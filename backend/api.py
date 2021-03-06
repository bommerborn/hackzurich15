import base64
import logging
import requests
import json

from suds.client import Client

from flask import Flask
from flask import request
from flask import jsonify

INST_ID = 7010
INST_PW = '7010VALORA'
UrlApi='http://hackzurich15.azurewebsites.net/api/';

app = Flask(__name__)

logging.basicConfig(level=logging.INFO)
api_client = Client('http://merit.axiomwebservices.com/MeritEChannelsAccessZurich/service.svc?singleWsdl')

def auth_user_token(token):
    if not token:
        return False
    username, password = base64.b64decode(token).split(':', 1)
    result = auth_user(username, password)
    return result

def auth_user(username, password):
    customerLogin = api_client.factory.create('ns30:customerLoginParameters')
    customerLogin.institutionID = INST_ID
    customerLogin.institutionPassword = INST_PW
    customerLogin.instrumentNo = username
    customerLogin.instrumentType = 'E'
    customerLogin.password = password

    result = api_client.service.customerLogin(customerLogin)
    print str(result)
    if result.returnMessageOutput.responseMessageType != "I":
        return False

    return result

def account_details(account_id):
    accountDetailsParams = api_client.factory.create('ns30:accountDetailsParameters')
    accountDetailsParams.institutionID = INST_ID
    accountDetailsParams.institutionPassword = INST_PW
    accountDetailsParams.instrumentNo = account_id
    accountDetailsParams.instrumentType = 'A' # relationship no

    result = api_client.service.getAccountDetails(accountDetailsParams)
    if result.returnMessageOutput.responseMessageType != "I":
        return False

    return result

@app.route('/authenticate', methods=['POST'])
def link_card():
    username = request.form.get('username')
    password = request.form.get('password')
    push_token = request.form.get('push_token')

    if not push_token:
        return jsonify(status="err", error="no_push_token"), 400

    result = auth_user(username, password)
    if not result:
        return jsonify(status="err", error="invalid_login"), 401

    if len(result.loyaltyAccountSet.customerLogin_loyaltyAccountSet) < 1:
        return jsonify(status="err", error="no_loyality_acc"), 401

    externalAccountNo = result.loyaltyAccountSet.customerLogin_loyaltyAccountSet[0].externalAccountNo
    internalAccountNo = result.loyaltyAccountSet.customerLogin_loyaltyAccountSet[0].internalAccountNo
    print "Using AccountID " + str(externalAccountNo)

    result = account_details(externalAccountNo)
    if not result:
        return jsonify(status="err", error="acc_details"), 401

    print str(result)

    for ident in [externalAccountNo, internalAccountNo]:
        pushParams = api_client.factory.create('ns30:setUserDevicesParameters')
        pushParams.institutionID = INST_ID
        pushParams.institutionPassword = INST_PW
        pushParams.deviceName = "iOS_Device"
        pushParams.status = "A"
        pushParams.userProfile = "APP"
        pushParams.runOption = "A"
        pushParams.entityType = "CUS"
        pushParams.deviceToken = push_token
        pushParams.entity = ident

        print str(pushParams)

        result = api_client.service.setUserDevices(pushParams)

        print str(result)

        if result.returnMessageOutput.responseMessageType != "I":
            if result.returnMessageOutput.responseCode != "21902":
                return jsonify(status="err", error="push_token_reg"), 400

    return jsonify(status="ok", token=base64.b64encode(username + ":" + password))

@app.route('/dispatch_push', methods=['POST'])
def disp_push():
    result = auth_user_token(request.form.get('token'))
    
    externalAccountNo = result.loyaltyAccountSet.customerLogin_loyaltyAccountSet[0].externalAccountNo
    result = account_details(externalAccountNo)
    
    UserID = result.loyaltyAccountSetList.loyaltyAccountSet[0].accountID;

    transactionListParams = api_client.factory.create('ns30:transactionListParameters')
    transactionListParams.scheme = 1
    transactionListParams.institutionID = INST_ID
    transactionListParams.institutionPassword = INST_PW
    transactionListParams.entityID = UserID
    transactionListParams.runOption = 'A'
    transactionListParams.sortKeyName = 'TRANSACTION_DATE'
    transactionListParams.sortKeyDir = 'D'
    transactionListParams.pageSize = 10
    transactionListParams.pageNumber = 1

    result = api_client.service.getTransactionList(transactionListParams)
    print str(result)

    if result.returnMessageOutput.responseMessageType != "I":
        return jsonify(status="err", error="transactions"), 400

    if len(result.transactionSetList.transactionSet) < 1:
        return jsonify(status="err", error="no_transactions"), 400

    transactionAmount = int(float(result.transactionSetList.transactionSet[0].originalAmount) * 100)

    print "Transaction amount: " + str(transactionAmount)
    UrlNewTransaction = UrlApi + 'NewTransaction?userid='+str(UserID)+'&transactionAmountCents='+ str(transactionAmount)
    requests.get(UrlNewTransaction)

    return jsonify(status="ok")

@app.route('/get_info', methods=['GET'])
def get_info():
    result = auth_user_token(request.args.get('token'))

    if not result:
        return jsonify(status="err", error="invalid_login"), 401

    if len(result.loyaltyAccountSet.customerLogin_loyaltyAccountSet) < 1:
        return jsonify(status="err", error="no_loyality_acc"), 401

    externalAccountNo = result.loyaltyAccountSet.customerLogin_loyaltyAccountSet[0].externalAccountNo
    print "Using AccountID " + str(externalAccountNo)

    result = account_details(externalAccountNo)
    if not result:
        return jsonify(status="err", error="acc_details"), 401

    print str(result)

    email = result.loyaltyAccountSetList.loyaltyAccountSet[0].accountHolderEmail

    UserID=result.loyaltyAccountSetList.loyaltyAccountSet[0].accountID
    UrlShowCashBack=UrlApi + 'LastCashbackAmountOfUser?uid=' + str(UserID)
    LastCashBackAmount=requests.get(UrlShowCashBack)
    LastCashBackAmountValue=LastCashBackAmount.content

    user_info_url = UrlApi + 'User/' + str(UserID)
    user_info = requests.get(user_info_url)
    print "user info: " + str(user_info.content)

    try:
        user_info_parsed = json.loads(user_info.content)
        balance_eur = float(user_info_parsed['credit']) / 100.0
    except Exception:
        pass

    transactionListParams = api_client.factory.create('ns30:transactionListParameters')
    transactionListParams.scheme = 1
    transactionListParams.institutionID = INST_ID
    transactionListParams.institutionPassword = INST_PW
    transactionListParams.entityID = externalAccountNo
    transactionListParams.runOption = 'A'
    transactionListParams.sortKeyName = 'TRANSACTION_DATE'
    transactionListParams.sortKeyDir = 'D'
    transactionListParams.pageSize = 10
    transactionListParams.pageNumber = 1

    result = api_client.service.getTransactionList(transactionListParams)
    print str(result)
    if result.returnMessageOutput.responseMessageType != "I":
        return jsonify(status="err", error="transactions"), 400

    if len(result.transactionSetList.transactionSet) < 1:
        return jsonify(status="err", error="no_transactions"), 404

    last_transaction_date = result.transactionSetList.transactionSet[0].transactionDate
    last_transaction_category = result.transactionSetList.transactionSet[0].transactionCategoryDescription

    print "Balance: " + str(balance_eur)
    ret = jsonify(status="ok", balance=balance_eur, email=email, last_transaction_date=last_transaction_date, last_transaction_category=last_transaction_category)
    return ret

if __name__ == '__main__':
    app.run(host='0.0.0.0')
