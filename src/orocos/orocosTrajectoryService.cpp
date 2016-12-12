
#include <ignition/msgs.hh>
#include <ignition/transport.hh>

#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>

using namespace std;
using namespace RTT;
using namespace Orocos;


namespace TrajectoryService
{
    class GazeboCommunication
        : public TaskContext
    {

	// Create a transport node.
	ignition::transport::Node node;

 	// Prepare the input parameters.
	ignition::msgs::StringMsg req;
    public:
        /**
         * This example sets the interface up in the Constructor
         * of the component.
         */
        GazeboCommunication(std::string name)
            : RTT::TaskContext(name)
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

		this->addOperation("clear", &GazeboCommunication::clear, this, RTT::OwnThread).doc("Clears all trajectorys.");
		this->addOperation("delAll", &GazeboCommunication::delAll, this, RTT::OwnThread).doc("Deletes all trajectorys.");
		this->addOperation("pause", &GazeboCommunication::pause, this, RTT::OwnThread).doc("Pauses drawing of all trajectorys");
		this->addOperation("resume", &GazeboCommunication::resume, this, RTT::OwnThread).doc("Resumes drawing of all trajectorys.");
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

        void updateHook()
        {
        	//log(Info) << "Update !" <<endlog();
        }
        bool configureHook()
        {
		//this->setPeriod(0.5);
		//log(Info) << "Configure !" <<endlog();
        	return true;
        }
	bool startHook(){
		//log(Info) << "start !" <<endlog();
		return true;
	}
	void stopHook(){
		//log(Info) << "stop !" <<endlog();
		
	}
	void cleanupHook(){
		//log(Info) << "clean !" <<endlog();
		
	}
    };
}

ORO_CREATE_COMPONENT( TrajectoryService::GazeboCommunication )
