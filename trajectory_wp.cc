#include <gazebo/rendering/rendering.hh>
#include <gazebo/gazebo.hh>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>


namespace gazebo
{
	class SystemGUI : public SystemPlugin
	{

		private: struct lineObject{			
			rendering::DynamicLines* line;
			unsigned int draw:1; 
			unsigned int clear:1;
			unsigned int del:1;
		};
		
		private: rendering::ScenePtr scene;
		private: rendering::VisualPtr visual;
		
		private: std::map<std::string, struct lineObject> trajectoryObjects; 

		private: ignition::transport::Node node;
		private: std::string service_clear = "/trajectory/command/clear";
		private: std::string service_delAll = "/trajectory/command/delAll";
		private: std::string service_pause = "/trajectory/command/pause";
		private: std::string service_resume = "/trajectory/command/resume";
		private: std::string service_newTrajectory = "/trajectory/command/newTrajectory";
		private: std::string service_delTrajectory = "/trajectory/command/delTrajectory";
		private: std::string service_clearTrajectory = "/trajectory/command/clearTrajectory";
		private: std::string service_pauseTrajectory = "/trajectory/command/pauseTrajectory";
		private: std::string service_resumeTrajectory = "/trajectory/command/resumeTrajectory";
		private: std::string service_changeColor = "/trajectory/command/resumeTrajectory";
		
		
		private: int colorIndex = 0;
		private: std::string color[5] = { "Gazebo/Purple", "Gazebo/Yellow", "Gazebo/Green", "Gazebo/Red","Gazebo/White"};
      
                /////////////////////////////////////////////
                /// \brief Destructor
		public: virtual ~SystemGUI(){this->connections.clear();}

                /////////////////////////////////////////////
                /// \brief Called after the plugin has been constructed.
		public: void Load(int /*_argc*/, char ** /*_argv*/)
		{

			if (!node.Advertise(service_clear, &SystemGUI::clear, this))
			  {
			    std::cerr << "Error advertising service [" << service_clear << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_newTrajectory, &SystemGUI::newTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_newTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_delTrajectory, &SystemGUI::delTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_delTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_clearTrajectory, &SystemGUI::clearTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_clearTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_pauseTrajectory, &SystemGUI::pauseTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_pauseTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_resumeTrajectory, &SystemGUI::resumeTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_resumeTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_delAll, &SystemGUI::delAll, this))
			  {
			    std::cerr << "Error advertising service [" << service_delAll << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_pause, &SystemGUI::pause, this))
			  {
			    std::cerr << "Error advertising service [" << service_pause << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_resume, &SystemGUI::resume, this))
			  {
			    std::cerr << "Error advertising service [" << service_resume << "]" << std::endl;
			    return;
			  }

			this->connections.push_back(
			rendering::Events::ConnectCreateScene(
			boost::bind(&SystemGUI::InitScene, this)));

			this->connections.push_back(event::Events::ConnectPreRender(
			std::bind(&SystemGUI::Update, this)));
		}

                /////////////////////////////////////////////
                // \brief Called once after Load
		private: void Init(){}

                /////////////////////////////////////////////
                /// \brief Called every PreRender event. See the Load function.
		/// Checks flags for operations
		void Update()
		{
			for (auto &object : trajectoryObjects)
			{		

					if((object.second).clear)
					{
						
						(object.second).line->Clear();
						(object.second).line->Update();
						(object.second).clear = 0;
					}	

					else if((object.second).draw)
					{			
						
						rendering::VisualPtr vis = scene->GetVisual(object.first);
						math::Pose pose = vis->GetWorldPose();
						math::Vector3 vec = pose.pos;
						pointAdd((object.second).line,vec.x,vec.y,vec.z);
					}

					if((object.second).del)
					{
						visual->DeleteDynamicLine((object.second).line);
						trajectoryObjects.erase(object.first);
					}		
			}
		}

		

		/////////////////////////////////////////////
                ///Gets the scene and creates new visual.
		private: void InitScene()
		{	
			scene = rendering::get_scene();
			visual = gazebo::rendering::VisualPtr(new gazebo::rendering::Visual("bla", scene));
			visual->Load();
			visual->SetVisible(true);		
		}
		
		/////////////////////////////////////////////
                ///Adds a point to a given DynamicLine
		private: void pointAdd(rendering::DynamicLines* dl,double x,double y,double z)
		{
			dl->AddPoint(x,y,z,common::Color::White);
		}

		/////////////////////////////////////////////
                ///Checks if visual is existend.If so, generates new trajectory object.
		private: void newTrajectory(const ignition::msgs::StringMsg &_req)
		{
			rendering::VisualPtr vis = scene->GetVisual(_req.data());

			if(vis == nullptr)
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
				return;
			}

			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				trajectoryObjects[_req.data()] = {getLine(), 1, 0, 0};
			}
		}

		/////////////////////////////////////////////
                ///Creates new DynamicLines and initializes it.
		private: rendering::DynamicLines* getLine()
		{
			rendering::DynamicLines* line = visual->CreateDynamicLine(gazebo::rendering::RENDERING_LINE_STRIP);
			line->setMaterial(color[colorIndex]);
			incColorIndex();
			line->setVisibilityFlags(GZ_VISIBILITY_GUI);
			return line;
		}

		/////////////////////////////////////////////
                ///Increments the index of the colorsArray.	
		private: void incColorIndex()
		{
			if(colorIndex++ >= 4) colorIndex = 0;
		}

		/////////////////////////////////////////////
                ///Sets the clearFlag of all lineobjects.
		private: void clear(const ignition::msgs::StringMsg &_req)
		{
			for(auto &visual : trajectoryObjects)
			{
				(visual.second).clear = 1;
			}
		}

		/////////////////////////////////////////////
                ///Sets the deleteFlag and clearFlag of all lineobjects.
		private: void delAll(const ignition::msgs::StringMsg &_req)
		{
			for(auto &visual : trajectoryObjects)
			{
				(visual.second).clear = 1;
				(visual.second).del = 1;
			}
		}

		/////////////////////////////////////////////
                ///Sets the drawFlag of all lineObjects to zero.
		private: void pause(const ignition::msgs::StringMsg &_req)
		{
			for(auto &visual : trajectoryObjects)
			{
				(visual.second).draw = 0;
			}
		}

		/////////////////////////////////////////////
                ///Sets the drawFlag of all lineObjects.
		private: void resume(const ignition::msgs::StringMsg &_req)
		{
			for(auto &visual : trajectoryObjects)
			{
				(visual.second).draw = 1;
			}
		}

		/////////////////////////////////////////////
                ///Sets the clearFlag of a given lineObjects.
		private: void clearTrajectory(const ignition::msgs::StringMsg &_req)
		{
			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
			(trajectoryObjects.find(_req.data())->second.clear)=1;
			}
		}

		/////////////////////////////////////////////
                ///Sets the deleteFlag and the clearFlag of a given lineObjects.
		private: void delTrajectory(const ignition::msgs::StringMsg &_req)
		{
			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				(trajectoryObjects.find(_req.data())->second.clear) = 1;
				(trajectoryObjects.find(_req.data())->second.del) = 1;
			}
		}

		/////////////////////////////////////////////
                ///Sets the drawFlag of a given lineObjects to zero.
		private: void pauseTrajectory(const ignition::msgs::StringMsg &_req)
		{
			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				(trajectoryObjects.find(_req.data())->second.draw) = 0;
			}
		}
		
		/////////////////////////////////////////////
                ///Sets the drawFlag of a given lineObjects.
		private: void resumeTrajectory(const ignition::msgs::StringMsg &_req)
		{
			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				(trajectoryObjects.find(_req.data())->second.draw) = 1;
			}
		}
		/// All the event connections.
		private: std::vector<event::ConnectionPtr> connections;
};
		// Register this plugin with the simulator
		GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}

