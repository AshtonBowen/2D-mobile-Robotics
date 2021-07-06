class avoid : public ArAction
{
public: 
	avoid();
	virtual ~avoid(){}
	virtual ArActionDesired * fire(ArActionDesired d);
	ArActionDesired desiredState;
	bool isObjectToClose();

protected:
	int m_speed;

};
