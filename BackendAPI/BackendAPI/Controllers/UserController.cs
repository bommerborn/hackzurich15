using BackendAPI.Database;
using BackendAPI.Models;
using System.Collections.Generic;
using System.Linq;
using System.Web.Http;

namespace BackendAPI.Controllers
{
    public class UserController : ApiController
    {
		/// <summary>
		/// Gets user data. When this data is manipulate nothing will be changed on the server.
		/// </summary>
		/// <param name="id">The ID of the user information we'd like to get.</param>
		/// <returns>The user data if the user is found</returns>
		public IHttpActionResult GetUser(int id)
		{
			User res = DatabaseConnector.Instance.GetUserData(id);

			if (res == null)
			{
				return NotFound();
			}

            return Ok(res);
		}
    }
}
