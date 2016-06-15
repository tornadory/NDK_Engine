//
// Created by F1 on 5/5/2016.
//

#include "Static_Model.h"

int Static_Model::render(Mat4 mvp)
{
	if(!mat)
	{
		LOGW("Warning: tried rendering a skeletal model without assigning material\n");
		return 0;
	}

	mat->bind_material();
	mat->bind_value(Shader::PARAM_VERTICES, (void*) verts);
	mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);

	glDrawElements(GL_TRIANGLES, tri_vert_count, GL_UNSIGNED_INT, (void *) 0);

	return 1;
}

int Static_Model::load_model(const char* filepath)
{
	raw_data = (unsigned int*) File_Utils::load_raw_asset(filepath);
	if(!raw_data)
	{
		LOGE("Error: failed to load \"%s\"\n",filepath);
		return 0;
	}

	//File Schematics
	//First float is the vertex count
	//Second float is the triangle count * 3
	//List thereafter is the position (3 floats) of all vertices
	//List thereafter is the indices vertices that make up the triangles
	vertex_count = raw_data[0];
	tri_vert_count = raw_data[1];

	verts = (float*) (raw_data + 2);

	tri_verts = raw_data + 2 + (vertex_count*3) + (vertex_count*3) + (vertex_count*3);
	return 1;
}

int Static_Model::init_gl()
{
	glGenBuffers(1, &tri_verts_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(tri_vert_count * sizeof(unsigned int)), tri_verts, GL_STATIC_DRAW);

	return 1;
}

void Static_Model::term_gl()
{
	glDeleteBuffers(1,&tri_verts_buffer);
}
void Static_Model::unload_model()
{
	if(raw_data)
		free((void*)raw_data);
}

