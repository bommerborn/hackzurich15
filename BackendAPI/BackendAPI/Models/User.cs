
using BackendAPI.Database;
using BackendAPI.Reactive;

namespace BackendAPI.Models
{
	public class User
	{
		private int[] nextLevelAt = new int[]
		{
			500,
			1000,
			2000,
			5000,
			10000,
			20000,
			50000
		};

		private string[] levelTitles = new string[]
		{
			"Student",
			"Startup",
			"Progressor",
			"Innovator",
			"Big Player",
			"Crazy Kiosker",
			"King of All"
		};

		#region Properties
		private Observable<int> _uidObservable;

		public int uid
		{
			get { return _uidObservable.Value; }
			private set { _uidObservable.Value = value; }
		}

		private Observable<int> _creditObservable;
		public int credit
		{
			get { return _creditObservable.Value; }
			private set { _creditObservable.Value = value; }
		}

		private Observable<int> _accumulatedCreditObservable;
		public int accumulatedCredit
		{
			get { return _accumulatedCreditObservable.Value; }
			private set { _accumulatedCreditObservable.Value = value; }
		}

		private Observable<int> _level;
		public int level
		{
			get { return _level.Value; }
			private set { _level.Value = value; }
		}

		private Observable<int> _lastCardExpenses;
		public int lastCardExpenses
		{
			get { return _lastCardExpenses.Value; }
			set { _lastCardExpenses.Value = value; }
		}


		public string levelTitle
		{
			get { return levelTitles[level]; }
		}
		#endregion

		public User(int uid)
		{
			SetUpObservables();

			this.uid = uid;
			this.credit = 0;
			this.accumulatedCredit = 0;
			this.level = 1;

			SetUpSubscriptions();
			UpdateThisInDatabase();
		}

		public User(int uid, int credit, int accumulatedCredit, int level, int lastCardExpenses)
		{
			SetUpObservables();

			this.uid = uid;
			this.credit = credit;
			this.accumulatedCredit = accumulatedCredit;
			this.level = level;
			this.lastCardExpenses = lastCardExpenses;

			SetUpSubscriptions();
			UpdateThisInDatabase();
		}

		private void SetUpObservables()
		{
			_uidObservable = new Observable<int>();
			_creditObservable = new Observable<int>();
			_accumulatedCreditObservable = new Observable<int>();
			_level = new Observable<int>();
			_lastCardExpenses = new Observable<int>();
		}

		private void SetUpSubscriptions()
		{
			_uidObservable.Subscribe(_ => UpdateThisInDatabase());
			_creditObservable.Subscribe(_ => UpdateThisInDatabase());
			_accumulatedCreditObservable.Subscribe(_ => UpdateThisInDatabase());
			_accumulatedCreditObservable.Subscribe(_ => EvaluateLevel());
			_level.Subscribe(_ => UpdateThisInDatabase());
			_lastCardExpenses.Subscribe(_ => UpdateThisInDatabase());
		}

		private void EvaluateLevel()
		{
			int maxLevel = nextLevelAt.Length;

			while (level < maxLevel && accumulatedCredit >= nextLevelAt[level - 1])
			{
				level++;
			}
		}

		public void UpdateThisInDatabase()
		{
			DatabaseConnector.Instance.PutUserData(this);
		}

		public void AddCredit(int amount)
		{
			credit += amount;
			accumulatedCredit += amount;
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