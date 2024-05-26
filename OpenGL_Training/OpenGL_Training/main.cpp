/**
 * @file   : main.h
 * @author : Shuhei Matsushima
 *
 * @berief : main
 */

#include "Application.h"

/**
 *
 */
int main()
{
	Application app;
	if (app.tryInitGL()) app.run();
}