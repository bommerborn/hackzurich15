using BackendAPI.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace BackendAPI.Controllers
{
    public class LastCashbackAmountOfUserController : ApiController
    {
		public IHttpActionResult GetLastCashbackAmountOfUser(int uid)
		{
			int res = DatabaseConnector.Instance.GetLastCashbackAmount(uid);

			return Ok(res);
		}
    }
}
