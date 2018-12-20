entry {
	Book = {
		name = [[p-]],
		sheets = {
			{
				name = [[p-]],
				cell_ws = {
					{
						col = [[a]],
						size = 2.75,
					},
					{
						col = [[b]],
						size = 1.5,
					},
					{
						col = [[i]],
						size = 1.75,
					},
					{
						col = [[j]],
						size = 6.38,
					},
					{
						col = [[k]],
						size = 5.63,
					},
					{
						col = [[l]],
						size = 2.13,
					},
					{
						col = [[m]],
						size = 2,
					},
					{
						col = [[n]],
						size = 0.46,
					},
					{
						col = [[o]],
						size = 1.75,
					},
					{
						col = [[p]],
						size = 3.63,
					},
					{
						col = [[q]],
						size = 1.88,
					},
					{
						col = [[r]],
						size = 2,
					},
					{
						col = [[w]],
						size = 2.5,
					},
					{
						col = [[y]],
						size = 2.38,
					},
					{
						col = [[aa]],
						size = 2.25,
					},
					{
						col = [[ac]],
						size = 2,
					},
					{
						col = [[ad]],
						size = 2.13,
					},
					{
						col = [[af]],
						size = 2,
					},
					{
						col = [[ag]],
						size = 2.15,
					},
					{
						col = [[ah]],
						size = 2,
					},
					{
						col = [[ai]],
						size = 1.88,
					},
					{
						col = [[aj]],
						size = 2,
					},
					{
						col = [[al]],
						size = 3.5,
					},
					{
						col = [[am]],
						size = 2,
					},
					{
						col = [[ao]],
						size = 3.75,
					},
					{
						col = [[ap]],
						size = 2,
					},
					{
						col = [[aq]],
						size = 2.25,
					},
					{
						col = [[ar]],
						size = 3.13,
					},
					{
						col = [[as]],
						size = 2,
					},
					{
						col = [[au]],
						size = 3,
					},
				},
				cell_hs = {
					{
						id = 1,
						size = 16,
					},
					{
						id = 2,
						size = 12,
					},
					{
						id = 3,
						size = 20,
					},
					{
						id = 6,
						size = 22.5,
					},
					{
						id = 7,
						size = 16,
					},
					{
						id = 8,
						size = 14,
					},
					{
						id = 11,
						size = 18,
					},
					{
						id = 12,
						size = 14,
					},
					{
						id = 23,
						size = 18,
					},
					{
						id = 22,
						size = 14,
					},
					{
						id = 23,
						size = 11,
					},
					{
						id = 24,
						size = 12,
					},
					{
						id = 25,
						size = 17,
					},
					{
						id = 30,
						size = 5,
					},
					{
						id = 31,
						size = 13,
					},
				},
				pos_rule = [[
					set_start_x(1);
					set_start_y(1);
				]],
				tables = {
					{
						type = 2,
						border = 0,
						pos_rule = [[
							set_table_x(1);
							set_table_y(13);
						]],
						init_rule = [[add_all();]],
						filter_rule = [[g_filter();]],
						group_rule = [[group_by_kind_group_section_mat();]],
						sort_rule = [[]],
						tables = {
							{
								type = 1,
								border = 0,
								init_rule = [[]],
								filter_rule = [[]],
								group_rule = [[]],
								sort_rule = [[]],
								cells = {
									{
										content = [[��Ʒӛ��]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("a12:e12");]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(5);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�L��]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("f12:i12");]],
										pos_rule = [[
											set_cell_x(6);
											set_cell_y(get_last_y());
											set_cell_w(4);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�g��]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("j12:j12");]],
										pos_rule = [[
											set_cell_x(10);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[����]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("k12:k12");]],
										pos_rule = [[
											set_cell_x(11);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�t��]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("l12:n12");]],
										pos_rule = [[
											set_cell_x(12);
											set_cell_y(get_last_y());
											set_cell_w(3);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�俼]],
										content_rule = [[]],
										style = [[����-12]],
										--pos_rule = [[set_cell_pos("o12:p12");]],
										pos_rule = [[
											set_cell_x(15);
											set_cell_y(get_last_y());
											set_cell_w(2);
											set_cell_h(1);
										]],
										border = 1,
									},
								},
							},
							{
								type = 1,
								border = 0,
								init_rule = [[add_all();]],
								filter_rule = [[g_filter_by_super_kind_group_section_mat();]],
								group_rule = [[equ();]],
								cells = {
									{
										content = [[KIND:]],
										content_rule = [[]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[KIND]],
										content_rule = [[content_by_kind();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[GROUP:]],
										content_rule = [[]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[GROUP]],
										content_rule = [[content_by_group();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[SECTION:]],
										content_rule = [[]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[SECTION]],
										content_rule = [[content_by_section();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[MAT:]],
										content_rule = [[]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[MAT]],
										content_rule = [[content_by_mat();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(get_last_x()+1);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
								},
							},
							{
								type = 1,
								border = 0,
								init_rule = [[add_all();]],
								filter_rule = [[g_filter_by_super_kind_group_section_mat();]],
								group_rule = [[group_by_part_no();]],
								sort_rule = [[sort_by_part_no();]],
									--	newsheet_rule = [[newsheet_by_row(21);]],
								cells = {
									{
										content = [[��Ʒӛ��]],
										content_rule = [[content_by_part_no();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(1);
											set_cell_y(get_last_y()+1);
											set_cell_w(5);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�L��]],
										content_rule = [[content_by_length();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(6);
											set_cell_y(get_last_y());
											set_cell_w(4);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�g��]],
										content_rule = [[content_by_weight();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(10);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[����]],
										content_rule = [[content_by_count();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(11);
											set_cell_y(get_last_y());
											set_cell_w(1);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�t��]],
										content_rule = [[content_by_weight_sum();]],
										style = [[����-12]],
										pos_rule = [[
											set_cell_x(12);
											set_cell_y(get_last_y());
											set_cell_w(3);
											set_cell_h(1);
										]],
										border = 1,
									},
									{
										content = [[�俼]],
										content_rule = [[set_content_s("");]],
										style = [[����-9]],
										pos_rule = [[
											set_cell_x(15);
											set_cell_y(get_last_y());
											set_cell_w(2);
											set_cell_h(1);
										]],
										border = 1,
									},
								},
							},
						},
					},
				},
			},
		},
		style_db = {
			css = {
				{
					type = 0,
					name = [[����-14]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 14,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-12]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 12,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 3,
				},
				{
					type = 0,
					name = [[����-10]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 10,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-9]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 9,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-8]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 8,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-7]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 7,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 1,
					name = [[����-12]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 12,
					blod = 0,
					italic = 0,
					h_align = 4,
					v_align = 3,
					precision = 1,
					bit = 0,
					addends = 0,
				},
			},
		},
	},
}

