#include <vector>
#include <memory>

#include <irrlicht.h>

class Dispatcher
{
public:
    typedef std::vector< std::shared_ptr<class Aircraft> > Aircrafts;
    Dispatcher();
    ~Dispatcher();

    void start();
    void execute();
    void stop();
    const Aircrafts& getAircrafts() const;
    bool evalShot(const irr::core::line3df&);
    irr::u32 getAircraftsRemaining() const;
    irr::u32 getPoints() const;

private:
    irr::u32 lastDispatchMS;
    Aircrafts aircrafts;
    bool active;

    irr::u32 aircraftsRemaining, points;

    void dispatchAircraft();
};
