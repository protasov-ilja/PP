using lab4.Controllers;
using lab4.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab4.Views
{
	public partial class InputForm : Form
	{
		private readonly InputFormController _inputFormController;

		public InputForm(DataManager data)
		{
			InitializeComponent();

			_inputFormController = new InputFormController(data);
			SubscribeToEvents();
		}

		private void SubscribeToEvents()
		{
			_inputFormController.ListCreated += ShowTimeList;
			inputText.TextChanged += _inputFormController.OnInputFileNameChanged;
			outputText.TextChanged += _inputFormController.OnOutputFileNameChanged;
			iterationsText.TextChanged += _inputFormController.OnAmountOfIterationsChanged;
			getResultButton.MouseClick += (sender, EventArgs) => { _inputFormController.OnGetResultButtonClicked(sender, EventArgs, asyncCheckBox.Checked); }; ;
		}

		public void ShowTimeList(List<long> times, bool isAsync)
		{
			MessageBox.Show($"Work { (isAsync ? "async" : "sync") }:\n middle: { times.Sum(time => time) / times.Count }");

			timeList.Items.Clear();
			foreach (var item in times)
			{
				timeList.Items.Add(item.ToString());
			}
		}
	}
}
