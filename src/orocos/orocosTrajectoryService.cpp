
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
		this->addOperation("newTrajectory", &GazeboCommunication::newTrajectoryModel, this, RTT::OwnThread).doc("Adds trajectory of the specific object.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("newTrajectoryModel", &GazeboCommunication::newTrajectoryModel, this, RTT::OwnThread).doc("Adds trajectory of the specific model.")
			.arg("model", "Name of the model");
		this->addOperation("newTrajectoryLink", &GazeboCommunication::newTrajectoryLink, this, RTT::OwnThread).doc("Add tajectory to link of specific model.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("delTrajectory", &GazeboCommunication::delTrajectoryModel, this, RTT::OwnThread).doc("Deletes trajectory of the specific object.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("delTrajectoryModel", &GazeboCommunication::delTrajectoryModel, this, RTT::OwnThread).doc("Deletes trajectory of the specific model.")
			.arg("model", "Name of the model");
		this->addOperation("delTrajectoryLink", &GazeboCommunication::delTrajectoryLink, this, RTT::OwnThread).doc("Deletes trajectory of the specific link.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("clearTrajectory", &GazeboCommunication::clearTrajectoryModel, this, RTT::OwnThread).doc("Clears trajectory of specific object.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("clearTrajectoryModel", &GazeboCommunication::clearTrajectoryModel, this, RTT::OwnThread).doc("Clears trajectory of specific model.")
			.arg("model", "Name of the model");
		this->addOperation("clearTrajectoryLink", &GazeboCommunication::clearTrajectoryLink, this, RTT::OwnThread).doc("Clears trajectory of specific link.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("pauseTrajectory", &GazeboCommunication::pauseTrajectoryModel, this, RTT::OwnThread).doc("Pauses drawing of a specific trajectory.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("pauseTrajectoryModel", &GazeboCommunication::pauseTrajectoryModel, this, RTT::OwnThread).doc("Pauses drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("pauseTrajectoryLink", &GazeboCommunication::pauseTrajectoryLink, this, RTT::OwnThread).doc("Pauses drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("resumeTrajectory", &GazeboCommunication::resumeTrajectoryModel, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("resumeTrajectoryModel", &GazeboCommunication::resumeTrajectoryModel, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model");
		this->addOperation("resumeTrajectoryLink", &GazeboCommunication::resumeTrajectoryLink, this, RTT::OwnThread).doc("Resumes drawing of a specific trajectory.")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("newCustomTrajectory", &GazeboCommunication::newCustomTrajectory, this, RTT::OwnThread).doc("Creates a static line holder.")
			.arg("model", "Name of the static line model");

		this->addOperation("addPoint", &GazeboCommunication::addPoint, this, RTT::OwnThread).doc("Adds a point to a staticLine.")
			.arg("model", "Name of the model")
			.arg("x", "X coordinate of point")
			.arg("y", "Y coordinate of point")
			.arg("z", "Z coordinate of point");

		this->addOperation("addSquare", &GazeboCommunication::addSquare, this, RTT::OwnThread).doc("Adds a square to a staticLine.")
			.arg("model", "Name of the model")
			.arg("x", "X coordinate of point")
			.arg("y", "Y coordinate of point")
			.arg("z", "Z coordinate of point");

		this->addOperation("setLifecycle", &GazeboCommunication::setLifecycleModel, this, RTT::OwnThread).doc("Changes length of trajectory.")
			.arg("visual", "Name of the visualobject")
			.arg("length", "Length of the trajectory");
		this->addOperation("setLifecycleModel", &GazeboCommunication::setLifecycleModel, this, RTT::OwnThread).doc("Changes length of trajectory.")
			.arg("model", "Name of the model")
			.arg("length", "Length of the trajectory");
		this->addOperation("setLifecycleLink", &GazeboCommunication::setLifecycleLink, this, RTT::OwnThread).doc("Changes length of trajectory.")
			.arg("model", "Name of the model")
			.arg("link", "Name of the link")
			.arg("length", "Length of the trajectory");

		this->addOperation("activateLifecycle", &GazeboCommunication::activateLifecycleModel, this, RTT::OwnThread).doc("Adds a lifecylce to line. Default value 3000 Points")
			.arg("visual", "Name of the visualobject");
		this->addOperation("activateLifecycleModel", &GazeboCommunication::activateLifecycleModel, this, RTT::OwnThread).doc("Adds a lifecylce to line. Default value 3000 Points")
			.arg("model", "Name of the model");
		this->addOperation("activateLifecycleLink", &GazeboCommunication::activateLifecycleLink, this, RTT::OwnThread).doc("Adds a lifecylce to line. Default value 3000 Points")
			.arg("model", "Name of the model")
			.arg("link","Name of the link");

		this->addOperation("deactivateLifecycle", &GazeboCommunication::deactivateLifecycleModel, this, RTT::OwnThread).doc("removes lifecycle from line.")
			.arg("visual", "Name of the visualobject");
		this->addOperation("deactivateLifecycleModel", &GazeboCommunication::deactivateLifecycleModel, this, RTT::OwnThread).doc("removes lifecycle from line.")
			.arg("model", "Name of the model");
		this->addOperation("deactivateLifecycleLink", &GazeboCommunication::deactivateLifecycleLink, this, RTT::OwnThread).doc("removes lifecycle from line.")
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

	void activateLifecycleModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/activateLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void activateLifecycleLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/activateLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;	
	}

	void deactivateLifecycleModel(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/deactivateLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void deactivateLifecycleLink(std::string model,std::string link)
	{
		req.set_data(model+"::"+link);
		bool executed = node.Request("/trajectory/command/deactivateLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;	
	}

	void newCustomTrajectory(std::string model)
	{
		req.set_data(model);
		bool executed = node.Request("/trajectory/command/newCustomTrajectory", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void addPoint(std::string model,double x,double y,double z)
	{
		req.set_data(model+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z));
		bool executed = node.Request("/trajectory/command/addPoint", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void addSquare(std::string model,double x,double y,double z)
	{
		req.set_data(model+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z));
		bool executed = node.Request("/trajectory/command/addStaticSquare", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}

	void setLifecycleModel(std::string model,int length)
	{
		req.set_data(model+" "+std::to_string(length));
		bool executed = node.Request("/trajectory/command/setLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}
	void setLifecycleLink(std::string model,std::string link,int length)
	{
		req.set_data(model+"::"+link+" "+std::to_string(length));
		bool executed = node.Request("/trajectory/command/setLifecycle", req);
		if (!executed) std::cerr << "Service call failed" << std::endl;
	}
    };
}
ORO_SERVICE_NAMED_PLUGIN(TrajectoryService::GazeboCommunication, "TrajectoryService")
