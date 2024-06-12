#include "core/Game.hpp"
#include "core/glm.hpp"
using namespace cmgt;
using namespace glm;
class FirstGame : public Game
{
public:
	FirstGame(ivec2 resolution, string name);
	~FirstGame();
protected:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnExit() override;
private:

};
