#include <gazebo/rendering/rendering.hh>
#include <gazebo/gazebo.hh>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <ignition/math.hh>


namespace gazebo
{
	class SystemGUI : public SystemPlugin
	{

		private: struct lineObject{
			rendering::DynamicLines* line;
			unsigned int draw:1; 
			unsigned int clear:1;
			unsigned int del:1;
			unsigned int lifecycle:1;
			int length;
			int index;
		};

		private: int lcLength = 3000;
		
		private: rendering::ScenePtr scene;
		private: rendering::VisualPtr visual;
		
		private: std::map<std::string, struct lineObject> trajectoryObjects; 

		private: ignition::transport::Node node;

		private: std::string service_clear = "/trajectory/command/clear";
		private: std::string service_delAll = "/trajectory/command/delAll";
		private: std::string service_pause = "/trajectory/command/pause";
		private: std::string service_resume = "/trajectory/command/resume";
		private: std::string service_newTrajectory = "/trajectory/command/newTrajectory";
		private: std::string service_newCustomTrajectory = "/trajectory/command/newCustomTrajectory";
		private: std::string service_addPoint = "/trajectory/command/addPoint";
		private: std::string service_delTrajectory = "/trajectory/command/delTrajectory";
		private: std::string service_clearTrajectory = "/trajectory/command/clearTrajectory";
		private: std::string service_pauseTrajectory = "/trajectory/command/pauseTrajectory";
		private: std::string service_resumeTrajectory = "/trajectory/command/resumeTrajectory";
		private: std::string service_activateLifecycle = "/trajectory/command/activateLifecycle";
		private: std::string service_setLifecycle = "/trajectory/command/setLifecycle";
		private: std::string service_deactivateLifecycle = "/trajectory/command/deactivateLifecycle";
		private: std::string service_addStaticSquare = "/trajectory/command/addStaticSquare";
		private: int colorIndex = 0;
		private: std::string color[8] = { "Gazebo/Purple", "Gazebo/Yellow", "Gazebo/Green", "Gazebo/Red","Gazebo/White", "Gazebo/Yellow","Gazebo/Turquoise","Gazebo/Blue" };

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
			if (!node.Advertise(service_newCustomTrajectory, &SystemGUI::newCustomTrajectory, this))
			  {
			    std::cerr << "Error advertising service [" << service_newCustomTrajectory << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_addPoint, &SystemGUI::addPoint, this))
			  {
			    std::cerr << "Error advertising service [" << service_addPoint << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_setLifecycle, &SystemGUI::setLifecycle, this))
			  {
			    std::cerr << "Error advertising service [" << service_setLifecycle << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_deactivateLifecycle, &SystemGUI::deactivateLifecycle, this))
			  {
			    std::cerr << "Error advertising service [" << service_deactivateLifecycle << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_activateLifecycle, &SystemGUI::activateLifecycle, this))
			  {
			    std::cerr << "Error advertising service [" << service_activateLifecycle << "]" << std::endl;
			    return;
			  }
			if (!node.Advertise(service_addStaticSquare, &SystemGUI::addStaticSquare, this))
			  {
			    std::cerr << "Error advertising service [" << service_addStaticSquare << "]" << std::endl;
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
						clearHandler(object.second);
					}	

					else if((object.second).draw)
					{				
						
						drawHandler(object.second,object.first);
					}
					else if((object.second).lifecycle)
					{					
						cycleHandler(object.second,object.first);
					}

					if((object.second).del)
					{
						delHandler(object.second,object.first);
					}		
			}
		}

		/////////////////////////////////////////////
		/// Clears the line and his clearFlag.
		private: void clearHandler(struct lineObject &object)
		{
			(object).line->Clear();
			(object).line->Update();
			(object).clear = 0;
		}

		/////////////////////////////////////////////
		/// Gets the coordinates of the visual and adds it to line object.
		private: void drawHandler(struct lineObject &object,std::string name)
		{
			rendering::VisualPtr vis = scene->GetVisual(name);
			if(vis!=nullptr)
			{
				math::Pose pose = vis->GetWorldPose();
				math::Vector3 vec = pose.pos;
				pointAdd((object).line,vec.x,vec.y,vec.z);
			}
		}

		/////////////////////////////////////////////
		/// Gets the coordinates of the visual and adds it to line object.
		private: void cycleHandler(struct lineObject &object,std::string name)
		{
			rendering::VisualPtr vis = scene->GetVisual(name);
			if(vis!=nullptr)
			{
				if(object.line->GetPointCount()==object.length)
				{
					math::Pose pose = vis->GetWorldPose();
					math::Vector3 vec = pose.pos;
					ignition::math::Vector3d vec3;
					vec3.Set(vec.x,vec.y,vec.z);
					for(int i = (object.length -1) ; i >= 0 ;i--)
					{
						if(i==0) object.line->SetPoint(0,vec3);
						else object.line->SetPoint(i,object.line->Point(i-1));
					}
				}
				else
				{
					math::Pose pose = vis->GetWorldPose();
					math::Vector3 vec = pose.pos;
					pointAdd((object).line,vec.x,vec.y,vec.z);
				}
			}
		}

		/////////////////////////////////////////////
		/// Deletes lineObject and the entry in trajectoryObjects.
		private: void delHandler(struct lineObject &object,std::string name)
		{
			visual->DeleteDynamicLine((object).line);
			trajectoryObjects.erase(name);
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
				trajectoryObjects[_req.data()] = {getLine(), 1, 0, 0, 1,lcLength,0};
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
			if(colorIndex++ >= 7) colorIndex = 0;
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

		/////////////////////////////////////////////
		///Sets the drawFlag of a given lineObjects.
		private: void newCustomTrajectory(const ignition::msgs::StringMsg &_req)
		{
			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				trajectoryObjects[_req.data()] = {getLine(), 1, 0, 0, 0,lcLength,0};
			}
		}

		/////////////////////////////////////////////
		///Adds a point to trajectory.
		///Cuts string in name and coordinate.
		private: void addPoint(const ignition::msgs::StringMsg &_req)
		{
			std::vector<std::string> array;
			std::size_t pos = 0, found;
			while((found = _req.data().find_first_of(' ', pos)) != std::string::npos)
			{
				array.push_back(_req.data().substr(pos, found - pos));
				pos = found+1;
			}
			array.push_back(_req.data().substr(pos));

			if(trajectoryObjects.find(array[0]) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
			pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1]),std::stod(array[2]),std::stod(array[3]));
			}
		}

		/////////////////////////////////////////////
		///Adds a square to static trajectory.
		///Cuts string in name and coordinate.
		private: void addStaticSquare(const ignition::msgs::StringMsg &_req)
		{
			std::vector<std::string> array;
			std::size_t pos = 0, found;
			while((found = _req.data().find_first_of(' ', pos)) != std::string::npos)
			{
				array.push_back(_req.data().substr(pos, found - pos));
				pos = found+1;
			}
			array.push_back(_req.data().substr(pos));

			if(trajectoryObjects.find(array[0]) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1])-0.01,std::stod(array[2])-0.01,std::stod(array[3]));
				pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1])+0.01,std::stod(array[2])-0.01,std::stod(array[3]));
				pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1])+0.01,std::stod(array[2])+0.01,std::stod(array[3]));
				pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1])-0.01,std::stod(array[2])+0.01,std::stod(array[3]));
				pointAdd((trajectoryObjects.find(array[0])->second).line,std::stod(array[1])-0.01,std::stod(array[2])-0.01,std::stod(array[3]));
				

			}
		}

		/////////////////////////////////////////////
		///Actives lifecycle mode.
		private: void activateLifecycle(const ignition::msgs::StringMsg &_req)
		{

			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				(trajectoryObjects.find(_req.data())->second.draw) = 0;
				(trajectoryObjects.find(_req.data())->second.clear) = 1;
				(trajectoryObjects.find(_req.data())->second.lifecycle) = 1;
			}
		}

		/////////////////////////////////////////////
		///Deactivates lifecycle and return to normal draw mode.
		private: void deactivateLifecycle(const ignition::msgs::StringMsg &_req)
		{

			if(trajectoryObjects.find(_req.data()) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				(trajectoryObjects.find(_req.data())->second.draw) = 1;
				(trajectoryObjects.find(_req.data())->second.clear) = 1;
				(trajectoryObjects.find(_req.data())->second.lifecycle) = 0;
			}
		}

		/////////////////////////////////////////////
		///Sets number of points to display.
		///Cuts string in name and number.
		private: void setLifecycle(const ignition::msgs::StringMsg &_req)
		{
			std::vector<std::string> array;
			std::size_t pos = 0, found;
			while((found = _req.data().find_first_of(' ', pos)) != std::string::npos)
			{
				array.push_back(_req.data().substr(pos, found - pos));
				pos = found+1;
			}
			array.push_back(_req.data().substr(pos));

			if(trajectoryObjects.find(array[0]) == trajectoryObjects.end())
			{
				std::cerr << "Error " << _req.data() << " not found" << std::endl;
			}
			else
			{
				((trajectoryObjects.find(array[0])->second).draw) = 0;
				((trajectoryObjects.find(array[0])->second).clear) = 1;
				((trajectoryObjects.find(array[0])->second).lifecycle) = 1;
				((trajectoryObjects.find(array[0])->second).length) = std::stoi(array[1]);
			}			
		}

		/// All the event connections.
		private: std::vector<event::ConnectionPtr> connections;
};
		// Register this plugin with the simulator
		GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}

