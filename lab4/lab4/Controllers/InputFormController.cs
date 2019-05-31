using lab4.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Windows.Forms;

namespace lab4.Controllers
{
	public sealed class InputFormController
	{
		private DataManager _data;
		private int _amountOfIterations;

		public event Action<List<long>, bool> ListCreated;

		public InputFormController(DataManager data)
		{
			_data = data;
		}

		public void OnAmountOfIterationsChanged(object sender, EventArgs e)
		{
			var textBox = (TextBox)sender;
			if (textBox.TextLength != 0 && int.TryParse(textBox.Text, out var value))
			{
				_amountOfIterations = value;
			}
			else
			{
				textBox.Text = "0";
				_amountOfIterations = 0;
			}
		}

		public void OnInputFileNameChanged(object sender, EventArgs e)
		{
			var textBox = (TextBox)sender;
			_data.InputFileName = textBox.Text;
		}

		public void OnOutputFileNameChanged(object sender, EventArgs e)
		{
			var textBox = (TextBox)sender;
			_data.OutputFileName = textBox.Text;
		}

		public async void OnGetResultButtonClicked(object sender, MouseEventArgs e, bool isAsync)
		{
			var iterationsTimeList = new List<long>();
			for (var i = 0; i < _amountOfIterations; ++i)
			{
				var timer = Stopwatch.StartNew();
				if (isAsync)
				{
					await _data.WriteDataFromUrlAsync();
				}
				else
				{
					var thread = new Thread(_data.WriteDataFromUrlSync);
					thread.Start();
					thread.Join();
				}
				
				timer.Stop();
				iterationsTimeList.Add(timer.ElapsedMilliseconds);
			}

			ListCreated?.Invoke(iterationsTimeList, isAsync);			
		}
	}
}
