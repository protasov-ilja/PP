using lab3.PrimitiveTypes;
using System.Collections.Generic;
using System.Threading;

namespace lab3
{
	public sealed class PiGenerator
	{
		const int ThreadsAmount = 2;

		public int StepsAmount { get; set; }
		public int Timeout { get; set; }

		private double _pi = 0;
		private ICriticalSection _criticalSection;

		public PiGenerator(int stepsAmount, int timeout, int spinsCount)
		{
			StepsAmount = stepsAmount;
			Timeout = timeout;
			_criticalSection = new CriticalSection();
			_criticalSection.SetSpinCount(spinsCount);
		}

		public double GetGeneratedPi(EnterType enterType)
		{
			_pi = 0;
			var step = 1 / (double)StepsAmount;
			int stepsAmountPerThread = StepsAmount / ThreadsAmount;
			var threads = CreateThreads(enterType, step, stepsAmountPerThread);
			foreach (var thread in threads)
			{
				thread.Join();
			}

			return _pi;
		}

		private IEnumerable<Thread> CreateThreads(EnterType enterType, double step, int stepsAmountPerThread)
		{
			var threads = new List<Thread>();
			for (var i = 0; i < ThreadsAmount; ++i)
			{
				var thread = new Thread(CalculatePi);
				thread.Start(new ArgsThread
				{
					Left = i * stepsAmountPerThread,
					Right = (i + 1) * stepsAmountPerThread,
					Step = step,
					EnterType = enterType
				});

				threads.Add(thread);
			}

			return threads;
		}

		private void CalculatePi(object args)
		{
			var data = (ArgsThread)args;
			for (var i = data.Left; i < data.Right; ++i)
			{
				var x = (i + 0.5) * data.Step;
				if (data.EnterType == EnterType.Enter)
				{
					_criticalSection.Enter();
				}
				else
				{
					while (!_criticalSection.TryEnter(Timeout)) ;
				}

				_pi += 4.0 / (1.0 + x * x) * data.Step;
				_criticalSection.Leave();
			}
		}
	}
}
