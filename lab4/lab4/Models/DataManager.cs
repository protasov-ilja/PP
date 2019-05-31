using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace lab4.Models
{
	public sealed class DataManager
	{
		const string resourcesFolderName = "Resources";
		const int DefaultCurrenciesCount = 6;

		public string InputFileName { get; set; }
		public string OutputFileName { get; set; }
		public int IterationsAmount { get; set; }

		private string _directoryPath;
		private string _resourcesPath;
		private Api _api;

		public DataManager()
		{
			_api = new Api();
			_directoryPath = Directory.GetCurrentDirectory();
			_resourcesPath = Path.Combine(_directoryPath, resourcesFolderName);
			if (!Directory.Exists(_resourcesPath))
			{
				Directory.CreateDirectory(_resourcesPath);
			}
		}

		public async Task WriteDataFromUrlAsync()
		{
			var getInputCurrencesTask = GetCurrencesFromInputFile();
			var getDataTask = _api.GetCurrenciesData();
			await Task.WhenAll(getInputCurrencesTask, getDataTask);
			
			var inputCurrences = await getInputCurrencesTask;
			var data = await getDataTask;

			var isInputFound = inputCurrences != null;

			var outputFilePath = Path.Combine(_resourcesPath, $"{ OutputFileName }.json");

			var counter = 0;
			using (var writer = new StreamWriter(outputFilePath))
			{
				IDictionary<string, JToken> currenciesData = data.Valute;
				foreach (var currency in currenciesData)
				{
					if ((isInputFound && inputCurrences.Contains(currency.Key)) || (!isInputFound && counter < DefaultCurrenciesCount))
					{
						writer.WriteLineAsync($"{currency.Value["Nominal"]} {currency.Key} по курсу {currency.Value["Value"]}");
						counter++;
					}
				}
			}
		}

		public void WriteDataFromUrlSync()
		{
			var inputCurrences = GetCurrencesFromInputFile().Result;
			var isInputFound = inputCurrences != null;
			var data = _api.GetCurrenciesData().Result;

			var outputFilePath = Path.Combine(_resourcesPath, $"{ OutputFileName }.json");

			var counter = 0;
			using (var writer = new StreamWriter(outputFilePath))
			{
				IDictionary<string, JToken> currenciesData = data.Valute;
				foreach (var currency in currenciesData)
				{
					if ((isInputFound && inputCurrences.Contains(currency.Key)) || (!isInputFound && counter < DefaultCurrenciesCount))
					{
						writer.WriteLine($"{currency.Value["Nominal"]} {currency.Key} по курсу {currency.Value["Value"]}");
						counter++;
					}
				}
			}
		}

		private async Task<List<string>> GetCurrencesFromInputFile()
		{
			var inputFilePath = Path.Combine(_resourcesPath, $"{ InputFileName }.json");
			if (!File.Exists(inputFilePath))
			{
				return null;
			}

			using (var reader = new StreamReader(inputFilePath))
			{
				var file = await reader.ReadToEndAsync();
				return JsonConvert.DeserializeObject<List<string>>(file);
			}
		}
	}
}
