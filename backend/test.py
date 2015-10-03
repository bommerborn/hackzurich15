import logging
logging.basicConfig(level=logging.INFO)

from suds.client import Client
url = 'http://merit.axiomwebservices.com/MeritEChannelsAccessZurich/service.svc?singleWsdl'
client = Client(url)

print str(client)

param = client.factory.create('ns30:merchantListParameters')
param.institutionID = 7010
param.institutionPassword = '7010VALORA'
result = client.service.getMerchantList(param)
print result

accountDetailsParams = client.factory.create('ns30:accountDetailsParameters')
accountDetailsParams.institutionID = 7010
accountDetailsParams.institutionPassword = '7010VALORA'
accountDetailsParams.instrumentNo = '5267504000117697'
accountDetailsParams.instrumentType = 'R'

result = client.service.getAccountDetails(accountDetailsParams)
print result


transactionListParams = client.factory.create('ns30:transactionListParameters')
transactionListParams.scheme = 1
transactionListParams.institutionID = 7010
transactionListParams.institutionPassword = '7010VALORA'
transactionListParams.entityID = '5267504000117697'
transactionListParams.runOption = 'R'

result = client.service.getTransactionList(transactionListParams)
print result

client2 = Client("http://merit.axiomwebservices.com/MeritEChannelsTransactionsZurich/service.svc?singleWsdl")
print str(client2)