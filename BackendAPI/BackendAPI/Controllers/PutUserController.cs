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
    public class PutUserController : ApiController
	{
		/// <summary>
		/// Adds a new or changes an existing user based on the identifier
		/// </summary>
		/// <param name="id">The user identifier. If the id you provide has not been assigned yet a new one will be created</param>
		/// <param name="currency">The currency the user should have from now on</param>
		/// <returns>Nothing</returns>
		public IHttpActionResult GetPutUser(int id, int creditCents)
		{
			DatabaseConnector.Instance.PutUserData(new User(id, creditCents));
			return Ok();
		}
	}
}
