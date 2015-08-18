#include <cstdlib>
#include <GameEngine.hh>
#include <Menu.hh>
#include <vector>
#include <Graph.hh>
#include <Gameplay.hh>
#include <Maps.hh>
#include <Cursor.hh>

int main()
{
    Maps m;

    m.create(100, 100, 10);

    Gameplay g("toto de merde");

    g.addPlayer(1, "Toto");
    g.addPlayer(3, "Tata");
    g.addPlayer(2, "Tutu");
    g.run();
    g.dump();
    std::string map = g.getCharMap(SIDE / 2, 1);

    std::vector<int> orient;
    gdl::GameEngine engine;

    orient.push_back(DOWN);
    if (engine.initialize() == false)
    {
        std::cout << "Failed to initialize game engine" << std::endl;
        return (EXIT_FAILURE);
    }
    
    engine.initMenu();
    while (engine.updateMenu() == true)
        engine.draw();
    return EXIT_SUCCESS;
}
