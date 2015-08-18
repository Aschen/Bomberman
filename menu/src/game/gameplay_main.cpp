#include "Gameplay.hh"

int main(void)
{
  Maps m;

  m.create(100, 100, 35);

  Gameplay g("toto");

  g.addPlayer(1, "Toto");
  g.addPlayer(3, "Tata");
  g.addPlayer(2, "Tutu");
  g.run();
  g.dump();
  std::string s = g.getCharMap(12, 1);
  g.resetPlayers();
  return 0;
}
