using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace lab4.Models
{
	public sealed class Api
	{
		private const string FileName = "daily_json.js";
		private readonly Uri _webAddress;
		private readonly HttpClient _client;

		public Api()
		{
			_webAddress = new Uri("https://www.cbr-xml-daily.ru/");
			_client = new HttpClient { BaseAddress = _webAddress };
		}

		public async Task<dynamic> GetCurrenciesData()
		{
			var response = await _client.GetAsync(FileName);
			if (response.StatusCode != HttpStatusCode.OK)
			{
				return null;
			}

			var json = await response.Content.ReadAsStringAsync();
			return (json != null) ? JsonConvert.DeserializeObject(json) : null;
		}
	}
}
