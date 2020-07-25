using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;


public partial class _Default : System.Web.UI.Page
{
    public string Out = "";
    protected void Page_Load(object sender, EventArgs e)
    {
        
        Class obj = new Class();
        string endpoint="public/trending-news-data";

       // Parameters required (These are sent as POST)
        string input = "date=2020-07-25";
        
        //Out Variable used on Default.aspx.cs to display Json using Javascript.
         Out = obj.send(endpoint, input);
         
    }
}