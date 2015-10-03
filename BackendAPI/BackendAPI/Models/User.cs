using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BackendAPI.Models
{
	public class User
	{
		public User(int uid, int credit)
		{
			this.uid = uid;
			this.credit = credit;
		}

		public int uid { get; private set; }
		public int credit { get; private set; }

		public void AddCredit(int amount)
		{
			credit += amount;
		}

		/// <summary>
		/// Retrieves credit from this user. Return true or false if it was a success.
		/// </summary>
		/// <param name="amount">The amount of value that needs to be retrieved from the user</param>
		/// <returns>Boolean representing if the user had enough funds and if the value has been retrieved</returns>
		public bool UseCredit(int amount)
		{
			if (credit < amount)
			{
				return false;
			}

			credit -= amount;
			return true;
		}
	}
}