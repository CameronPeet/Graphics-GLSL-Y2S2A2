#include "Utils.h"
#include "CLogger.h"


struct FrameBuffer
{
	~FrameBuffer()
	{
		glDeleteFramebuffers(1, &fbo);
	}

	FrameBuffer()
	{
		glGenFramebuffers(1, &fbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{
			CLogManager::GetInstance().Write("Frame Buffer created : SUCCESSFULLY");
		}

		//Gen texture to write to
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1200, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//attach to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	GLuint fbo;
	GLuint texture;

};