

#include <ignition/msgs.hh>
#include <ignition/transport.hh>





int main(int argc, char **argv)
{
  // Create a transport node.
  ignition::transport::Node node;

  // Prepare the input parameters.
  ignition::msgs::StringMsg req;

	if(argc >=2){
		std::string arg1 = argv[1];

		if(arg1 =="clear")
		{
			std::cerr << "clear" << std::endl;

			  // Request the "/oneway" service.
			req.set_data("HELLO");
			bool executed = node.Request("/trajectory/command/clear", req);
			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;
		}
		if(arg1 =="delAll")
		{
			std::cerr << "deleted all" << std::endl;

			  // Request the "/oneway" service.
			req.set_data("HELLO");
			bool executed = node.Request("/trajectory/command/delAll", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;
		}
		if(arg1 =="pause")
		{
			std::cerr << "paused" << std::endl;

			  // Request the "/oneway" service.
			req.set_data("HELLO");
			bool executed = node.Request("/trajectory/command/pause", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;
		}
		if(arg1 =="resume")
		{
			std::cerr << "resumed" << std::endl;

			  // Request the "/oneway" service.
			req.set_data("HELLO");
			bool executed = node.Request("/trajectory/command/resume", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;
		}
		else if(arg1 == "newTrajectory" && argc==3)
		{
			std::cerr << "newTrajectory Model" << std::endl;
			std::string arg2 = argv[2];
			req.set_data(arg2);
			bool executed = node.Request("/trajectory/command/newTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "newTrajectory" && argc==4)
		{
			std::cerr << "newTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string linkName = argv[3];
						
			req.set_data(modelName+"::"+linkName);
			bool executed = node.Request("/trajectory/command/newTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "delTrajectory" && argc==3)
		{
			std::cerr << "delTrajectory Model" << std::endl;
			std::string arg2 = argv[2];
			req.set_data(arg2);
			bool executed = node.Request("/trajectory/command/delTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "delTrajectory" && argc==4)
		{
			std::cerr << "delTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string linkName = argv[3];
						
			req.set_data(modelName+"::"+linkName);
			bool executed = node.Request("/trajectory/command/delTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "clearTrajectory" && argc==3)
		{
			std::cerr << "clearTrajectory Model" << std::endl;
			std::string arg2 = argv[2];
			req.set_data(arg2);
			bool executed = node.Request("/trajectory/command/clearTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "clearTrajectory" && argc==4)
		{
			std::cerr << "clearTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string linkName = argv[3];
						
			req.set_data(modelName+"::"+linkName);
			bool executed = node.Request("/trajectory/command/clearTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "pauseTrajectory" && argc==3)
		{
			std::cerr << "pauseTrajectory Model" << std::endl;
			std::string arg2 = argv[2];
			req.set_data(arg2);
			bool executed = node.Request("/trajectory/command/pauseTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "pauseTrajectory" && argc==4)
		{
			std::cerr << "pauseTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string linkName = argv[3];
						
			req.set_data(modelName+"::"+linkName);
			bool executed = node.Request("/trajectory/command/pauseTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "resumeTrajectory" && argc==3)
		{
			std::cerr << "resumeTrajectory Model" << std::endl;
			std::string arg2 = argv[2];
			req.set_data(arg2);
			bool executed = node.Request("/trajectory/command/resumeTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "resumeTrajectory" && argc==4)
		{
			std::cerr << "resumeTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string linkName = argv[3];
						
			req.set_data(modelName+"::"+linkName);
			bool executed = node.Request("/trajectory/command/resumeTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}

		else if(arg1 == "newCustomTrajectory" && argc==3)
		{
			std::cerr << "newTrajectory" << std::endl;
			std::string modelName = argv[2];
			
						
			req.set_data(modelName);
			bool executed = node.Request("/trajectory/command/newCustomTrajectory", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}

		else if(arg1 == "addPoint" && argc==6)
		{
			std::cerr << "resumeTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string x = argv[3];
			std::string y = argv[4];
			std::string z = argv[5];
						
			req.set_data(modelName+" "+x+" "+y+" "+z);
			bool executed = node.Request("/trajectory/command/addPoint", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "addSquare" && argc==6)
		{
			std::cerr << "resumeTrajectory Link" << std::endl;
			std::string modelName = argv[2];
			std::string x = argv[3];
			std::string y = argv[4];
			std::string z = argv[5];
						
			req.set_data(modelName+" "+x+" "+y+" "+z);
			bool executed = node.Request("/trajectory/command/addStaticSquare", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "activateLifecycle" && argc==3)
		{
			std::cerr << "Lifecycle" << std::endl;
			std::string modelName = argv[2];
			
						
			req.set_data(modelName);
			bool executed = node.Request("/trajectory/command/activateLifecycle", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "deactivateLifecycle" && argc==3)
		{
			std::cerr << "removed Lifecycle" << std::endl;
			std::string modelName = argv[2];
			
						
			req.set_data(modelName);
			bool executed = node.Request("/trajectory/command/deactivateLifecycle", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "setLifecycle" && argc==4)
		{
			std::cerr << "set Lifecycle" << std::endl;
			std::string modelName = argv[2];
			std::string length = argv[3];

						
			req.set_data(modelName+" "+length);
			bool executed = node.Request("/trajectory/command/setLifecycle", req);

			if (!executed)
				std::cerr << "Service call failed" << std::endl;
			return 1;

		}
		else if(arg1 == "help")
		{
			std::cerr << "clear,newTrajectory,delTrajectory,clearTrajectory,pauseTrajectory,resumeTrajectory,delALl,pause,resume,newCustomTrajectory,addPoint,addSquare,activateLifecycle,deactivateLifecycle" << std::endl;

		}
		else 
		{
			std::cerr << "wrong command" << std::endl;
		}
	}

return -1;

  
}
