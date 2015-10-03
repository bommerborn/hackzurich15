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
		private const float creditFraction = 0.1f;

		public IHttpActionResult GetNewTransaction(int userid, int transactionAmountCents)
		{
			User u = DatabaseConnector.Instance.GetUserData(userid);

			if(u == null)
			{
				u = new User(userid, 0);
			}

			DatabaseConnector.Instance.PutTransactionData(userid, transactionAmountCents);

			u.AddCredit((int)(transactionAmountCents * creditFraction));

			DatabaseConnector.Instance.PutUserData(u);

			return Ok();
		}
    }
}
