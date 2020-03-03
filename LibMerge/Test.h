#pragma once
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "JsonManager.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define D_VEC3(v) cout << v.x << "  " << v.y << "  " << v.z  << endl
#define D_VEC4(v) cout << v.x << "  " << v.y << "  " << v.z  << "  " << v.w << endl

void Test_4()
{
	Window& win = *Window::GetSingletionPtr();
	win.CreateWindow(800, 800);
	Document d = JsonManager::ReadFile("j1.json");
	int vlen;
	float * vertices = JsonManager::JsonToFloatArray(d["v3"].GetArray(), vlen);

	Shader shader = Shader("sample_box.vs", "sample_texture_mix.fs");
	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);
	Mesh m1 = Mesh(vertices, vlen, new int[2]{ 3, 5 }, 2);
	Texture t1 = Texture("res/img/container.jpg");
	Texture t2 = Texture("res/img/awesomeface.png");
	auto winptr = win.GetWinPtr();
	Transform t = Transform();
	t.SetPosition(vec3(0.0f, 0.0f, 0.0f));
	t.SetEulerAngle(vec3(0.0, 0.0f, 0.0));
	Camera cmr = Camera();
	cmr.GetTransform().SetPosition(vec3(0, 0, -3.0f));
	glm::mat4 trans(1.0f);
	glEnable(GL_DEPTH_TEST);
	auto old = t.GetPosition();
	float spd = 0.05f;
	float rspd = 0.5f;
	Transform& ct = cmr.GetTransform();
	while (!glfwWindowShouldClose(winptr))
	{
		//trans = rotate(trans, radians(1.0f), vec3(0, 0, 1.0f));
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		t.Rotate(vec3(1, 1, 1), 2);
		trans = cmr.GetProMatrix() * cmr.GetViewMatrix() * t.GetModelMatrix();
		shader.SetMatrix("transform", trans);
		t1.Bind(0);
		t2.Bind(1);
		glBindVertexArray(m1.GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(winptr);
		glfwPollEvents();

		
		if (glfwGetKey(winptr, GLFW_KEY_W) == GLFW_PRESS)
		{
			ct.Move(ct.GetUpDir() * spd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_S) == GLFW_PRESS)
		{
			ct.Move(ct.GetUpDir() * -spd);
			
		}
		else if (glfwGetKey(winptr, GLFW_KEY_A) == GLFW_PRESS)
		{
			ct.Move(ct.GetRightDir() * spd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_D) == GLFW_PRESS)
		{
			ct.Move(ct.GetRightDir() * -spd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_Z) == GLFW_PRESS)
		{
			ct.Move(ct.GetFrontDir() * spd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_X) == GLFW_PRESS)
		{
			ct.Move(ct.GetFrontDir() * -spd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_Q) == GLFW_PRESS)
		{
			//ct.Rotate(ct.GetUpDir(), rspd);
			ct.Rotate(UP * rspd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_E) == GLFW_PRESS)
		{
			//ct.Rotate(ct.GetUpDir(), -rspd);
			ct.Rotate(UP * -rspd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_R) == GLFW_PRESS)
		{
			
			ct.Rotate(ct.GetRightDir(), rspd);
			//ct.Rotate(RIGHT * rspd);
		}
		else if (glfwGetKey(winptr, GLFW_KEY_F) == GLFW_PRESS)
		{
			ct.Rotate(ct.GetRightDir(), -rspd);
			//ct.Rotate(RIGHT * -rspd);
		}

	}
}



void Test_3()
{
	auto win = Window::GetSinleton();
	win.CreateWindow(800, 800);
	Document d = JsonManager::ReadFile("j1.json");
	int vlen;
	float * vertices = JsonManager::JsonToFloatArray(d["v2"].GetArray(), vlen);
	int ilen;
	int * indexs = JsonManager::JsonToIntArray(d["i2"].GetArray(), ilen);
	Shader shader = Shader("sample_trans.vs", "sample_texture_mix.fs");
	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);
	Mesh m1 = Mesh(vertices, vlen, new int[3]{ 3, 6, 8 }, 3, indexs, ilen);
	Texture t1 = Texture("res/img/container.jpg");
	Texture t2 = Texture("res/img/awesomeface.png");
	auto winptr = win.GetWinPtr();
	Transform t = Transform();
	t.SetPosition(vec3(0.0f, 0.0f, 0.0f));
	mat4 view(1.0f);
	view = translate(view, vec3(0, 0, -3.0f));
	mat4 projection(1.0f);
	projection = perspective(radians(45.0f), 1.0f, 0.1f, 1000.0f);
	glm::mat4 trans(1.0f);
	trans = projection * view * t.GetModelMatrix();
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(winptr))
	{
		//trans = rotate(trans, radians(1.0f), vec3(0, 0, 1.0f));
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		t.SetEulerAngle(t.GetEulerAngle() + vec3(0.0f, 1.0f, 1.0f));
		trans = projection * view * t.GetModelMatrix();
		shader.SetMatrix("transform", trans);
		t1.Bind(0);
		t2.Bind(1);
		glBindVertexArray(m1.GetVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(winptr);
		glfwPollEvents();
	}
}

//ÌùÍ¼
void Test_2()
{
	auto win = Window::GetSinleton();
	win.CreateWindow(800, 800);
	Document d = JsonManager::ReadFile("j1.json");
	int vlen;
	float * vertices = JsonManager::JsonToFloatArray(d["v2"].GetArray(), vlen);
	int ilen;
	int * indexs = JsonManager::JsonToIntArray(d["i2"].GetArray(), ilen);
	Shader shader = Shader("sample_texture.vs", "sample_texture_mix.fs");
	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);
	Mesh m1 = Mesh(vertices, vlen, new int[3]{ 3, 6, 8 }, 3, indexs, ilen);
	Texture t1 = Texture("res/img/container.jpg");
	Texture t2 = Texture("res/img/awesomeface.png");
	auto winptr = win.GetWinPtr();
	while (!glfwWindowShouldClose(winptr))
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		t1.Bind(0);
		t2.Bind(1);
		glBindVertexArray(m1.GetVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(winptr);
		glfwPollEvents();
	}
}

void Test_1()
{
	auto win = Window::GetSinleton();
	win.CreateWindow(800, 800);
	Document d = JsonManager::ReadFile("j1.json");
	int len;
	float * vertices = JsonManager::JsonToFloatArray(d["v1"].GetArray(), len);
	Shader shader = Shader("sample.vs", "sample.fs");
	Mesh m1 = Mesh(vertices, len, new int[2]{ 3, 6 }, 2);
	auto winptr = win.GetWinPtr();
	while (!glfwWindowShouldClose(winptr))
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader.GetShaderProgram());
		glBindVertexArray(m1.GetVAO()); 
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(winptr);
		glfwPollEvents();
	}
}


