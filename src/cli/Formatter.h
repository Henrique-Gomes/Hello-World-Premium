#pragma once

class Formatter {
public:
	static void init();
	static void setFormat(int color, int backColor, bool underline);
	static void resetFormat();
};