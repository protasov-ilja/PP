using lab4.Models;
using lab4.Views;
using System;
using System.Windows.Forms;

namespace lab4
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			DataManager data = new DataManager();
			Application.Run(new InputForm(data));
		}
	}
}
