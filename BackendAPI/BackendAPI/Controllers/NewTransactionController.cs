using BackendAPI.Database;
using BackendAPI.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace BackendAPI.Controllers
{
    public class NewTransactionController : ApiController
    {
		public IHttpActionResult GetNewTransaction(int userid, int newCardBalanceInCents)
		{
			User u = DatabaseConnector.Instance.GetUserData(userid);

			if(u == null)
			{
				u = new User(userid);
			}

			int transactionAmountCents = newCardBalanceInCents - u.lastCardExpenses;

			u.lastCardExpenses = newCardBalanceInCents;

			float cashbackFraction = CalculateCashbackFraction(u.level);

			int cashbackAmount = (int)(transactionAmountCents * cashbackFraction);

			u.AddCredit(cashbackAmount);

			DatabaseConnector.Instance.PutTransactionData(userid, transactionAmountCents, cashbackAmount);

			DatabaseConnector.Instance.PutUserData(u);

			return Ok();
		}

		private float CalculateCashbackFraction(int level)
		{
			switch (level)
			{
				case 1:
					return .03f;
				case 2:
					return .05f;
				case 3:
					return .08f;
				case 4:
					return .1f;
				case 5:
					return .13f;
				case 6:
					return .16f;
				default:
					return .2f;
			}
		}
    }
}
