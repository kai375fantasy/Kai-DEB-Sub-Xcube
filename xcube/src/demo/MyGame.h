#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine//custom/MyEngineSystem.h" // �����־ϵͳͷ�ļ�

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		// ��¼�����һ���ƶ��ķ��� latest movement
		std::string lastDirection;


		void handleKeyEvents();
		void update();
		void render();
		void renderUI();

		void initSubsystem();   // ��ʼ����ϵͳ
		void cleanupSubsystem(); // ������ϵͳ
		
	public:
        MyGame();
		~MyGame();
		int runMainLoop(); // ��װ��ѭ���������쳣����
};

#endif // __TEST_GAME_H__