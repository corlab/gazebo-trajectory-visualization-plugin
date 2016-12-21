
#include <ignition/msgs.hh>
#include <ignition/transport.hh>

#include <rtt/plugin/ServicePlugin.hpp>
#include <rtt/base/ExecutableInterface.hpp>
#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>

using namespace std;
using namespace RTT;
using namespace Orocos;


namespace TrajectoryService
{
    class GazeboCommunication
        : public RTT::Service
    {

	// Create a transport node.
	ignition::transport::Node node;

 	// Prepare the input parameters.
	ignition::msgs::StringMsg req;
    public:
        

        GazeboCommunication(TaskContext* owner)
            : RTT::Service("TrajectoryService", owner)
        {
		this->addOperation("newTrajectoryModel", &GazeboCommunication::newTrajectoryModel, this, RTT::OwnThread).doc("Adds trajectory of the specific model.")
			.arg("model", "Name of the model");
		this->addOperation("newTrajectoryLink", &GazeboCommunication::newTrajectoryLink, this, RTT::OwnThread).doc("Add tajectory to link of specific model.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("delTrajectoryModel", &GazeboCommunication::delTrajectoryModel, this, RTT::OwnThread).doc("Deletes trajectory of the specific model.")
			.arg("model", "Name of the model");
		this->addOperation("delTrajectoryLink", &GazeboCommunication::delTrajectoryLink, this, RTT::OwnThread).doc("Deletes trajectory of the specific link.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("clearTrajectoryModel", &GazeboCommunication::clearTrajectoryModel, this, RTT::OwnThread).doc("Clears trajectory of specific model.")
			.arg("model", "Name of the model");
		this->addOperation("clearTrajectoryLink", &GazeboCommunication::clearTrajectoryLink, this, RTT::OwnThread).doc("Clears trajectory of specific link.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("pauseTrajectoryModel", &GazeboCommunication::pauseTrajectoryModel, this, RTT::OwnThread).doc("Pauses drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("pauseTrajectoryLink", &GazeboCommunication::pauseTrajectoryLink, this, RTT::OwnThread).doc("Pauses drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("resumeTrajectoryModel", &GazeboCommunication::resumeTrajectoryModel, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("resumeTrajectoryLink", &GazeboCommunication::resumeTrajectoryLink, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("newCustomTrajectory", &GazeboCommunication::newCustomTrajectory, this, RTT::OwnThread).doc(".")
			.arg("model", "Name of the model");

		this->addOperation("addPoint", &GazeboCommunication::addPoint, this, RTT::OwnThread).doc(".")
			.arg("model", "Name of the model")
			.arg("x", "")
			.arg("y", "")
			.arg("z", "");

		this->addOperation("setLifecycleModel", &GazeboCommunication::setLifecycleModel, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("setLifecycleLink", &GazeboCommunication::setLifecycleLink, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("removeLifecycleModel", &GazeboCommunication::removeLifecycleModel, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("removeLifecycleLink", &GazeboCommunication::removeLifecycleLink, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");
		


		this->addOperation("clear", &GazeboCommunication::clear, this, RTT::OwnThread).doc("Clears all trajectorys.");
		this->addOperation("delAll", &GazeboCommunication::delAll, this, RTT::OwnThread).doc("Deletes all trajectorys.");
		this->addOperation("pause", &GazeboCommunication::pause, this, RTT::OwnThread).doc("Pauses drawing of all trajectorys");
		this->addOperation("resume", &GazeboCommunication::resume, this, RTT::OwnThread).doc("Resumes drawing of all trajectorys.");
		
		this->doc("TrajectoryService service interface.");     
	}

	void newTrajectoryModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/newTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;

	}

	void newTrajectoryLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/newTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;

	}

	void delTrajectoryModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/delTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void delTrajectoryLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/delTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void clearTrajectoryModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/clearTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void clearTrajectoryLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/clearTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;

	}

	void pauseTrajectoryModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/pauseTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void pauseTrajectoryLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/pauseTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;

	}

	void resumeTrajectoryModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/resumeTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void resumeTrajectoryLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/resumeTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;	
	}

	void clear()
	{
		req.set_data("clear");
		bool executed = node.Request("/trajectory/command/clear", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;

	}

	void delAll()
	{
		req.set_data("delAll");
		bool executed = node.Request("/trajectory/command/delAll", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void pause()
	{
		req.set_data("pause");
		bool executed = node.Request("/trajectory/command/pause", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void resume()
	{
		req.set_data("HELLO");
		bool executed = node.Request("/trajectory/command/resume", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void setLifecycleModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/setLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void setLifecycleLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/setLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;	
	}

	void removeLifecycleModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/removeLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void removeLifecycleLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/removeLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;	
	}

	void newCustomTrajectory(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/newCustomTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void addPoint(std::string model,std::string x,std::string y,std::string z)
	{
		req.set_data(model+" "+x+" "+y+" "+z);
		bool executed = node.Request("/trajectory/command/addPoint", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}
    };
}
ORO_SERVICE_NAMED_PLUGIN(TrajectoryService::GazeboCommunication, "dot")
