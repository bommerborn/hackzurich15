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
    public class CreditController : ApiController
    {
		private const string IncreaseText = "increase", DecreaseText = "decrease";

		/// <summary>
		/// This call changes a user's credit.
		/// </summary>
		/// <param name="id">The User's ID</param>
		/// <param name="amount">The amount that should be added or removed</param>
		/// <param name="increaseordecrease">Parameter specifying if we're talking about an 'increase' or 'decrease'</param>
		/// <returns>A JSON with if the credit change was a succes</returns>
		public IHttpActionResult GetChangeCredit(int id, int amount, string increaseordecrease)
		{
			User u = DatabaseConnector.Instance.GetUserData(id);

			if(u == null)
			{
				return NotFound();
			}

			bool result = false;

			if(increaseordecrease == IncreaseText)
			{
				u.AddCredit(amount);
				result = true;
			}else if(increaseordecrease == DecreaseText)
			{
				result = u.UseCredit(amount);
			}
			else
			{
				return BadRequest("Unknow input parameter \"" + increaseordecrease + "\". Only \"" + IncreaseText + "\" and \"" + DecreaseText + "\" are accepted.");
			}
			
			DatabaseConnector.Instance.PutUserData(u);
			return Ok();
		}
	}
}
