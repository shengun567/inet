#ifndef __INET_OSPFV3INTERFACESTATE_H_
#define __INET_OSPFV3INTERFACESTATE_H_

#include <string>

#include "inet/common/INETDefs.h"
#include "inet/routing/ospf/v3/interface/Ospfv3Interface.h"

namespace inet {
namespace ospf {
namespace v3 {

class INET_API Ospfv3InterfaceState
{
  public:
    virtual void processEvent(Ospfv3Interface *interface, Ospfv3Interface::Ospfv3InterfaceEvent eventNum) = 0;
    virtual Ospfv3Interface::Ospfv3InterfaceFaState getState() const = 0;
    virtual ~Ospfv3InterfaceState() {};
    virtual std::string getInterfaceStateString() const = 0;

  protected:
    void changeState(Ospfv3Interface *intf, Ospfv3InterfaceState *newState, Ospfv3InterfaceState *currentState);
    void calculateDesignatedRouter(Ospfv3Interface *intf);
};

} // namespace v3
} // namespace ospf
}//namespace inet

#endif // __INET_OSPFV3INTERFACESTATE_H_
