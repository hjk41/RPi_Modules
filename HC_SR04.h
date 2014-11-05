#include <assert.h>
#include "common.h"
#include "RPi_GPIO.h"

class HC_SR04
{
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="HC_SR04" /> class.
    /// </summary>
    /// <param name="trig">The trigger pin.</param>
    /// <param name="echo">The echo pin.</param>
    /// <param name="maxDist">The maximum distance (in meters) you want to accept.
    /// By default, HC_SR04 measures up to 4 meters.</param>
    HC_SR04(int trig, int echo, double maxDist = 4)
        : m_trig(trig),
        m_echo(echo),
        m_maxDist(maxDist)
    {
        if (!GPIO::GPIOInitialized())
        {
            assert(GPIO::GPIOInit() == GPIO::GPIO_SUCCESS);
        }
        GPIO::GPIOSetOutput(m_trig);
        GPIO::GPIOSetInput(m_echo);
    }

    /// <summary>
    /// Finalizes an instance of the <see cref="HC_SR04"/> class.
    /// Sets the pins as input to avoid burning pin by wrong wiring.
    /// </summary>
    ~HC_SR04()
    {
        GPIO::GPIOSetInput(m_trig);
        GPIO::GPIOSetInput(m_echo);
    }

    /// <summary>
    /// Gets the distance with HC_SR04.
    /// </summary>
    /// <returns>Distance in meters.
    /// If there is error, return 0.</returns>
    double GetDist()
    {
        const static double soundSpeed = 343;
        double maxRTT = m_maxDist * 2 / soundSpeed;

        SetMaxPriority();

        double ts = GetTime();
        GPIO::GPIOSetHigh(m_trig);
        BusySleepUs(12);                  // send a 12us signal to device
        GPIO::GPIOSetLow(m_trig);

        bool success = true;
        while (!GPIO::GPIORead(m_echo))
        {
            if (GetTime() - ts >= maxRTT)
            {
                success = false;
                break;
            }
        }
        double tr = GetTime();			// rising edge

        while (GPIO::GPIORead(m_echo))
        {
            if (GetTime() - tr >= maxRTT)
            {
                success = false;
                break;
            }
        }
        double tf = GetTime();			// falling edge

        SetDefaultPriority();

        if (success)
        {
            return (tf - tr) * soundSpeed / 2;
        }
        else
        {
            return 0;
        }
    }

private:
    int m_trig;
    int m_echo;
    double m_maxDist;
};
