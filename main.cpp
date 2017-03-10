#include <iostream>
#include <cinatra/cinatra.h>
#include <ormpp/dbng.hpp>
#include <iguana/json.hpp>

int main()
{
	cinatra::cinatra<> app;
	app.route("/", [](cinatra::request const& req, cinatra::response& res)
	{
		//res.response_file("web/static/index.html");
		res.response_text("Your IP address is " + req.remote_endpoint().address().to_string());
	});

	app.set_static_path("./web/static");
	app.listen("0.0.0.0", "9000");
	app.run();

	return 0;
}