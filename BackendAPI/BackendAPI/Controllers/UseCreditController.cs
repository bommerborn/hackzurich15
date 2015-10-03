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
    public class UseCreditController : ApiController
    {
		///private const string IncreaseText = "increase", DecreaseText = "decrease";

		/// <summary>
		/// This call decreases a user's credit.
		/// </summary>
		/// <param name="id">The User's ID</param>
		/// <param name="amount">The amount that should be added or removed</param>
		public IHttpActionResult GetUseCredit(int userid, int amount)
		{
			User u = DatabaseConnector.Instance.GetUserData(userid);

			if(u == null)
			{
				u = new User(userid);
			}

			bool result = u.UseCredit(amount);

			return Ok(result);
		}
	}
}
