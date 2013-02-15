// Default empty project template
#ifndef Housingbbx_HPP_
#define Housingbbx_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class Housingbbx : public QObject
{
    Q_OBJECT
public:
    Housingbbx(bb::cascades::Application *app);
    virtual ~Housingbbx() {}
};


#endif /* Housingbbx_HPP_ */
