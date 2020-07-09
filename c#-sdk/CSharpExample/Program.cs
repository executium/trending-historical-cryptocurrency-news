using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpExample
{
    class Program
    {
        static void Main(string[] args)
        {
            CallApi();
            Console.ReadLine();
        }

        private static async void CallApi()
        {
            // Set Endpoint
            var endpoint = "public/trending-news-data";

            // Input payload that is send by POST method
            var input = new Dictionary<string, string> {{"date", "2020-07-03"}};

            // Initialize with Api Key and Api Secret
            var apiAccess = new ApiAccess(Config.Key, Config.Secret);

            // Post input payload to the specified endpoint
            var result = await apiAccess.Send(endpoint, input, new List<string>());

            // Write result
            Console.WriteLine(result);
        }
    }
}
