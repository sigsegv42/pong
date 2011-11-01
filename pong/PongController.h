#ifndef INCLUDED_PONG_CONTROLLER
#define INCLUDED_PONG_CONTROLLER

#include <hookah/Window.h>
#include <luxa/ComponentManager.h>
#include <luxa/Menu.h>
#include <input/KeyboardDevice.h>
#include <input/MouseDevice.h>
#include <gui/InputEventAdapter.h>

class PongScene;
class PongRenderer;

/**
 * The core game controller class
 */
class PongController
{
	public:
		PongController();

		bool run();

		bool exec(const v3D::CommandInfo & command, const std::string & param);
		bool execUI(const v3D::CommandInfo & command, const std::string & param);

	protected:
		void setMenuItemDefaults(const boost::shared_ptr<Luxa::Menu> & menu);

	private:
		boost::shared_ptr<PongScene> scene_;
		boost::shared_ptr<PongRenderer> renderer_;
		boost::shared_ptr<Luxa::ComponentManager> vgui_;
		boost::shared_ptr<Hookah::Window> window_;
		boost::shared_ptr<v3D::KeyboardDevice> keyboard_;
		boost::shared_ptr<v3D::MouseDevice> mouse_;
		boost::shared_ptr<v3D::CommandDirectory> directory_;
		boost::shared_ptr<InputEventAdapter> listenerAdapter_;
};

#endif // INCLUDED_PONG_CONTROLLER
