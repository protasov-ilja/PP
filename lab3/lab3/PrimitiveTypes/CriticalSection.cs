using System;
using System.Threading;

namespace lab3.PrimitiveTypes
{
	public sealed class CriticalSection : ICriticalSection
	{
		const int Timeout = 10;

		private readonly Mutex _mutex = new Mutex();
		private int _spinCount;

		public CriticalSection()
		{
			_spinCount = 0;
		}

		public void Enter()
		{
			int spinNumber = 0;
			while (!_mutex.WaitOne(0, false))
			{
				if (spinNumber == _spinCount)
				{
					spinNumber = 0;
					Thread.Sleep(Timeout);
				}

				spinNumber++;
			}
		}

		public void Leave()
		{
			_mutex.ReleaseMutex();
		}

		public void SetSpinCount(int count)
		{
			_spinCount = count;
		}

		public bool TryEnter(int timeout)
		{
			int spinNumber = 0;
			var startTime = DateTime.Now.Millisecond;
			while (!_mutex.WaitOne(0, false))
			{
				if (spinNumber == _spinCount)
				{
					spinNumber = 0;
					Thread.Sleep(Timeout);
				}

				spinNumber++;
				if (timeout <= DateTime.Now.Millisecond - startTime)
				{
					return false;
				}
			}

			return true;
		}
	}
}
