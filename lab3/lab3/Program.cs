using lab3.PrimitiveTypes;
using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace lab3
{
	class Program
	{
		static int Main(string[] args)
		{
			var arguments = new List<int>();
			if (!TryToConvertToIntList(args, out arguments))
			{
				return 1;
			}

			var generator = new PiGenerator(arguments[0], arguments[1], arguments[2]);

			var timer = Stopwatch.StartNew();
			var pi = generator.GetGeneratedPi(EnterType.Enter);
			timer.Stop();

			var workTime = timer.ElapsedMilliseconds;
			Console.WriteLine($"Pi: { pi }, Work time: { workTime } ms, Type: { EnterType.Enter }");

			timer = Stopwatch.StartNew();
			pi = generator.GetGeneratedPi(EnterType.TryEnter);
			timer.Stop();

			workTime = timer.ElapsedMilliseconds;
			Console.WriteLine($"Pi: { pi }, Work time: { workTime } ms, Type: { EnterType.TryEnter }");

			return 0;
		}

		private static bool TryToConvertToIntList(string[] args, out List<int> resultList)
		{
			resultList = null;
			if (args.Length != 3)
			{
				Console.WriteLine("Invalid arguments number.\n" +
					" Must be: lab3.exe <stepsCount> <timeout> <spinCount>");

				return false;
			}

			resultList = new List<int>();
			for (var i = 0; i < args.Length; ++i)
			{
				if (int.TryParse(args[i], out var value))
				{
					resultList.Add(value);
				}
				else
				{
					Console.WriteLine($"Invalid argument: { args[i] } not int number");

					return false;
				}
			}

			return true;
		}
	}
}
