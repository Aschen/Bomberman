#include "Gameplay.hh"

void see(std::string map, int mod)
{
  std::cout << "   ";
  for (int a = 0; a < mod; a++)
    std::cout << "[" << a << "]";

  for (int i = 0, l = map.size(); i < l; i++)
  {
    if (i % mod == 0)
    {      
      std::cout << std::endl;
      std::cout << "[" << i / mod << "]";
    }
    std::cout << "[" << map[i] << "]";
  }
  std::cout << std::endl << std::endl;
}

int main(int ac, char **av)
{
    /*
  Maps m;

  (void)av;
  (void)ac;
  m.create(30, 30, 35);

  Gameplay g("toto");

  g.addPlayer(1, "Toto");
  g.addPlayer(3, "Tata");
  g.addPlayer(2, "Tutu");  
  g.run();
  g.dump();
  see(g.getCharMap(5, 1), 11);
  see(g.getCharMap(5, 2), 11);
  see(g.getCharMap(5, 3), 11);
  return 0;
  */
}
