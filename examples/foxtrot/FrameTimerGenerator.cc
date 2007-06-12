#include "FrameTimerGenerator.h"
#include "FrameTimer.h"

#include <assert.h>

Define_Module_Like(FrameTimerGenerator,Trivial);

void FrameTimerGenerator::init(FrameTimer *parent)
{
	Enter_Method_Silent();
	char * lookupname;
	ft = parent;
	if (parent->owner->hasPar("GlobalTime"))
		lookupname = strdup(parent->owner->par("GlobalTime"));
	else
		lookupname = strdup("GlobalTime");
	gt = dynamic_cast<GlobalTime*>(parent->owner->getNode()->submodule(lookupname));
	if (gt == NULL)
		gt = dynamic_cast<GlobalTime*>(findModuleType(lookupname)->createScheduleInit(lookupname,parent->owner->getNode()));
	free(lookupname);	

	frames = new std::map<unsigned int,double>;
	timers = new std::map<unsigned int, cMessage*>;
}


void FrameTimerGenerator::nextFrame(unsigned int index)
{
	simtime_t now = gt->currentGlobalTime();
	if ((*frames)[index] == 0)
		return;
	assert(frames->find(index)!=frames->end());
	double count = floor(now/(*frames)[index]);
	ev <<"scheduling at "<<count<<"," <<((count+1)*(*frames)[index])<<endl;
	scheduleAt((count+1)*(*frames)[index],(*timers)[index]);
}

unsigned int FrameTimerGenerator::setFrameTimer(double period)
{
	unsigned int key = timers->size();
	while (timers->find(key)!=timers->end())
		key++;
	setFrameTimer(key,period);
	return key;
}

void FrameTimerGenerator::setFrameTimer(unsigned int index, double period)
{
	Enter_Method_Silent();
	cMessage *timer;
	assert(period>0);
	if (timers->find(index)==timers->end())
	{
		char buffer[255];
		sprintf(buffer,"frame timer %d",index);
		timer = new cMessage();
		timer->setKind(index);
		timer->setName(buffer);
		(*timers)[index] = timer;
	}
	else
	{
		timer = (*timers)[index];
		cancelFrameTimer(index);
	}
	(*frames)[index] = period;
	nextFrame(index);
}

void FrameTimerGenerator::cancelFrameTimer(unsigned int index)
{
	assert(frames->find(index)!=frames->end());
	if ((*timers)[index]->isScheduled())
		cancelEvent((*timers)[index]);
	(*frames)[index] = 0;
}

void FrameTimerGenerator::handleMessage(cMessage* msg)
{
	ft->handleFrameTimer(msg->kind());
	nextFrame(msg->kind());
}

FrameTimerGenerator::~FrameTimerGenerator()
{
	for (std::map<unsigned int,cMessage*>::const_iterator p=timers->begin();p!=timers->end();p++)
	{
		cancelFrameTimer(p->second->kind());
		delete p->second;
	}
	delete timers;
	delete  frames;
}

