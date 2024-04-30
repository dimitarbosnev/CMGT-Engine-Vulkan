#include "../core/Game.hpp"
#include "glm/glm.hpp"
using namespace cmgt;
using namespace glm;
class FirstGame : public Game
{
public:
	FirstGame(ivec2 resolution, string name, bool debug = false);
	~FirstGame();
protected:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnRender() override;
private:

};
