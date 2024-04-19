#ifndef EX2_ISUBSCRIBER_H
#define EX2_ISUBSCRIBER_H

class ISubscriber
{
public:
	virtual void Update() = 0;
private:
	virtual ~ISubscriber() = default;
};

#endif //EX2_ISUBSCRIBER_H
