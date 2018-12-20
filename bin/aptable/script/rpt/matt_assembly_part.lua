entry {
	book = {
		name = [[book-test.xls]],
		sheets = {
			{
				name = [[���]],
				pos_rule = [[
					set_start_x(1);
					set_start_y(1);
				]],
				tables = {
					{
						type = 2,
						init_rule = [[
							add_all();
							add_again();
						]],
						filter_rule = [[]],
						group_rule = [[group_by_no();]],
						sort_rule = [[sort_by_no();]],
						tables = {
							{
								type = 1,
								border = 1,
								pos_rule = [[
									set_table_x(2);
									set_table_y(get_last_y());
								]],
								init_rule = [[add_part_by_super_no();]],
								group_rule = [[group_by_no();]],
								cells = {
									{
										h = 200,
										content = [[]],
										content_rule = [[content_by_no();]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y());
											set_cell_w(4);
											set_cell_h(1);
										]],
									},
								},
							},
							{
								type = 1,
								border = 1,
								pos_rule = [[
									set_table_x(2);
									set_table_y(get_last_y()+1);
								]],
								init_rule = [[]],
								filter_rule = [[]],
								group_rule = [[]],
								sort_rule = [[]],
								cells = {
									{
										w = 800,
										h = 200,
										content = [[���]],
										content_rule = [[]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										w = 400,
										content = [[����]],
										content_rule = [[]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(2);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										w = 600,
										content = [[�ߴ�]],
										content_rule = [[]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(3);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										w = 600,
										content = [[����]],
										content_rule = [[]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(4);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
								},
							},
							{
								type = 1,
								border = 1,
								pos_rule = [[
									set_table_x(2);
									set_table_y(get_last_y()+1);
								]],
								init_rule = [[add_part_by_super_no();]],
								filter_rule = [[
									RSteel * t = get_curitem();
									if(strcmp(t->mat, "SS100") == 0){ 
										pass();
									}else{
										unpass();
									}
								]],
								group_rule = [[group_by_section();]],
								sort_rule = [[sort_by_section();]],
								cells = {
									{
										h = 200,
										content = [[]],
										content_rule = [[content_by_section();]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[]],
										content_rule = [[content_by_count();]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(2);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[]],
										content_rule = [[content_by_length_sum();]],
										style = [[С��]],
										pos_rule = [[
											set_cell_x(3);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[]],
										content_rule = [[content_by_weight();]],
										style = [[С��]],
										pos_rule = [[
											set_cell_x(4);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
								},
							},
							{
								type = 1,
								border = 1,
								pos_rule = [[
									set_table_x(2);
									set_table_y(get_last_y()+1);
								]],
								init_rule = [[add_part_by_super_no();]],
								group_rule = [[group_by_no();]],
								cells = {
									{
										h = 200,
										content = [[С��]],
										style = [[����]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
									},
									{
										content = [[]],
										content_rule = [[content_by_weight();]],
										style = [[С��]],
										pos_rule = [[
											set_cell_x(2);
											set_cell_y(get_last_y());
											set_cell_w(3);
											set_cell_h(1);
										]],
									},
								},
							},
						},
					},
					{
						type = 1,
						border = 1,
						pos_rule = [[
							set_table_x(2);
							set_table_y(get_last_y()+1);
						]],
						init_rule = [[add_all();add_again();]],
						group_rule = [[equ();]],
						cells = {
							{
								h = 300,
								content = [[�ܼ�]],
								style = [[����]],
								pos_rule = [[
									set_cell_x(1);
									set_cell_y(get_table_y());
									set_cell_w(1);
									set_cell_h(1);
								]],
							},
							{
								content_rule = [[
									double sum = get_curgroup_weight_sum();
									set_content_f(sum);
								]],
								style = [[С��]],
								pos_rule = [[
									set_cell_x(2);
									set_cell_y(get_table_y());
									set_cell_w(3);
									set_cell_h(1);
								]],
							},
						},
					},
				},
			},
		},
		style_db = {
			css = {
				{
					name = [[����]],
					font = [[����]],
					text_color = 3,
					back_color = 0,
					size = 60,
					blod = 1,
					italic = 0,
					h_allign = 3,
					v_allign = 2,
				},
				{
					name = [[����]],
					font = [[����]],
					text_color = 1,
					back_color = 35,
					size = 60,
					blod = 0,
					italic = 0,
					h_allign = 1,
					v_allign = 2,
					precision = 1,
					bit = 0,
					addends = 0,
				},
				{
					name = [[С��]],
					font = [[����]],
					text_color = 5,
					back_color = 35,
					size = 60,
					blod = 0,
					italic = 1,
					h_align = 4,
					v_align = 2,
					precision = 0.5,
					bit = 1,
					addends = 1,
				},
			},
		},
	},
}

