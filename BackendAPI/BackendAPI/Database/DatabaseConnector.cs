using System.Linq;
using System.Data.SqlClient;
using BackendAPI.Models;

namespace BackendAPI.Database
{
	public class DatabaseConnector
	{
		private const string DBURL = "uzyu5g08dx.database.windows.net,1433", DBName = "hackzurich15db", DBUser = "bvanderdrift", DBPW = "Hackzurich15";
		private const string UserTableName = "[dbo].[Users]", TransactionTableName = "[dbo].[Transactions]";

		private const string UIDColumn = "uid", CreditColumn = "credit";

		SqlConnection _connection;

		public void OpenConnection()
		{
			string connectionString = "server=" + DBURL + "; Database=" + DBName + "; User Id=" + DBUser + "; Password = " + DBPW + ";";
			_connection = new SqlConnection(connectionString);
			_connection.Open();
		}

		public void CloseConnection()
		{
			if (_connection.State != System.Data.ConnectionState.Broken && _connection.State != System.Data.ConnectionState.Closed)
			{
				_connection.Close();
			}
		}

		public User GetUserData(int id)
		{
			string cmd = "SELECT * FROM " + UserTableName + " WHERE " + UIDColumn + " = " + id + ";";
            SqlCommand sc = new SqlCommand(cmd, _connection);
			SqlDataReader sdr = sc.ExecuteReader();
			bool readSucces = sdr.Read();

			if (readSucces)
			{
				int uid = (int)sdr[UIDColumn];
				double fcredit = (double)sdr[CreditColumn];
				int credit = (int)fcredit;

				sdr.Close();
				return new User(uid, credit);
			}
			else
			{
				sdr.Close();
				return null;
			}
        }

		public void PutUserData(User u)
		{
			SqlCommand sc = new SqlCommand("UPDATE " + UserTableName + " SET " + CreditColumn + "=" + u.credit + " WHERE " + UIDColumn + " = " + u.uid + ";", _connection);
			int count = sc.ExecuteNonQuery();

			if(count == 0)
			{
				sc = new SqlCommand("INSERT INTO " + UserTableName + " ([" + UIDColumn + "], [" + CreditColumn + "]) VALUES (" + u.uid + ", '" + u.credit + "');", _connection);
				sc.ExecuteNonQuery();
			}
		}

		public int CountTransactions()
		{
			SqlCommand sc = new SqlCommand("SELECT COUNT(*) FROM " + TransactionTableName, _connection);
			SqlDataReader sdr = sc.ExecuteReader();
			sdr.Read();
			int res = (int)sdr[0];
			sdr.Close();

			return res;
		}

		public int CountTransactions(int uid)
		{
			SqlCommand sc = new SqlCommand("SELECT COUNT(*) FROM " + TransactionTableName + " WHERE uid = " + uid + ";", _connection);
			SqlDataReader sdr = sc.ExecuteReader();
			sdr.Read();
			int res = (int)sdr[0];
			sdr.Close();

			return res;
		}

		public void PutTransactionData(int uid, int amountCents)
		{
			int tid = CountTransactions();
			SqlCommand sc = new SqlCommand("INSERT INTO " + TransactionTableName + " VALUES (" + tid + ", " + uid + ", " + amountCents + ")", _connection);
			sc.ExecuteNonQuery();
		}

		~DatabaseConnector()
		{
			CloseConnection();
		}

		#region Singleton

		static private DatabaseConnector _instance;

		static public DatabaseConnector Instance
		{
			get
			{
				if(_instance == null)
				{
					_instance = new DatabaseConnector();
					_instance.OpenConnection();
				}

				return _instance;
			}
		}

		#endregion
	}
}