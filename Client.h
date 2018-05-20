class Client
{
	protected:
		enum {MENU,GAME,PAUSE,OPTIONS,HELP,EXIT}gameState;
	public:
		Client();
		int MainLoop();
		~Client();
}
