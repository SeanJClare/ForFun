#include <vector>
#include <string>
class Vertex{
public:
    Vertex(char id);
    Vertex(Vertex* initalAdd, char id);
    ~Vertex();

    void connect(Vertex* toConnect);
    bool disconnect(Vertex* toRemove);

    std::string toString();
private:
    std::vector<Vertex*> connections;
    char id;
};