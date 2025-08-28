import streamlit as st
import pandas as pd
import copy as co
import csv as cs
import os
import re
import io
import zipfile as zp

def row_addition(file):
    roll_pattern = r'^\d{4}[A-Z]{2}\d{2}$'
    name_pattern = r'^[A-Z][a-z]+ [A-Z][a-z]+$'
    emai_pattern = r'^[a-z]+@[a-z]+\.co\.in$'
    inp_roll = input('Roll : ')
    while not re.match(roll_pattern, inp_roll):
        print('Invalid roll..')
        inp_roll = input('Roll : ')
    inp_name = input('name : ')
    while not re.match(inp_name, name_pattern):
        print('Invalid name..')
        inp_name = input('name : ')
    inp_emai = input('email : ')
    while not re.match(emai_pattern, inp_emai):
        print('Invalid email..')
        inp_emai = input('email : ')
    row = [inp_roll, inp_name, inp_emai]
    row_adder(file, row)
    
def row_adder(csv_file, row):
    with open(csv_file, mode = 'a', newline='') as file:
        writter = cs.writer(file)
        writter.writerow(row)    
        
def output_generator(inp_data_set):
    braches = {}
    branch_count = {}

    for st in inp_data_set.itertuples(index=True):
        if st.Roll[4:6] not in braches.keys():
            braches.update({st.Roll[4:6] : [[st.Roll, st.Name, st.Email]]})
            branch_count.update({st.Roll[4:6] : 1})
        else:
            braches[st.Roll[4:6]].append([st.Roll, st.Name, st.Email])
            branch_count[st.Roll[4:6]] += 1

    folder = 'output_batch_list'
    os.makedirs(folder, exist_ok=True)

    for st in braches.keys():
        df = pd.DataFrame(braches[st], columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder, f"{st}.csv")
        df.to_csv(csv_path, index = True)
        
    group_nums = int(input(" what are the total number of groups you want to create ? "))

    max_person_per_group = len(inp_data_set)//group_nums + 1

    brach_arr = []
    for st in braches.keys() : 
        brach_arr.append(st)
        
    tot_branches = len(brach_arr)


    ##Branch_wise_mix-------
    g_i = 0
    b_i = 0
    groups_branch_wise = []
    branch_count_copy = co.deepcopy(branch_count)
    completed_branches = 0
    while g_i < group_nums:
        group = []
        group_mem_count = 0
        while (group_mem_count < max_person_per_group) and (completed_branches != tot_branches):
            if branch_count_copy[brach_arr[b_i]] != 0:
                pick_up_index = branch_count[brach_arr[b_i]] - branch_count_copy[brach_arr[b_i]]
                branch_count_copy[brach_arr[b_i]] -= 1
                if branch_count_copy[brach_arr[b_i]] == 0:
                    completed_branches += 1
                group.append(braches[brach_arr[b_i]][pick_up_index])
                b_i = (b_i + 1) % tot_branches
                group_mem_count += 1
            else:
                b_i = (b_i + 1) % tot_branches
        groups_branch_wise.append(group)
        g_i += 1

    folder_2 = 'output_batch_wise_mix'
    os.makedirs(folder_2, exist_ok=True)

    i = 1
    for g in groups_branch_wise:
        df = pd.DataFrame(g, columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder_2, f"g_{i}.csv")
        df.to_csv(csv_path, index = True)
        i += 1
        
    ##uniform_mix-------
    sorted_branch_count = dict(sorted(branch_count.items(), key=lambda item: item[1], reverse=True))
    sorted_branch_arr = []
    for k in sorted_branch_count.keys():
        sorted_branch_arr.append(k)
    branch_count_copy_2 = co.deepcopy(branch_count)
    g_i = 0

    max_br = sorted_branch_arr[0]
    uniform_groups = []
    pick_up_index = 0
    completed_branches = 0
    while g_i < group_nums: 
        group_i = [] 
        group_mem_count = 0
        while (group_mem_count != max_person_per_group) and (completed_branches != tot_branches):
            if branch_count_copy_2[max_br] != 0:
                pick_up_index = branch_count[max_br] - branch_count_copy_2[max_br]
                group_i.append(braches[max_br][pick_up_index])
                group_mem_count += 1
                branch_count_copy_2[max_br] -= 1
                if branch_count_copy_2[max_br] == 0:
                    completed_branches += 1
            else:
                max_br = max(branch_count_copy_2, key = branch_count_copy_2.get)
        max_br = max(branch_count_copy_2, key = branch_count_copy_2.get)
        uniform_groups.append(group_i)
        g_i += 1
        
    folder_3 = 'output_uniform_mix'
    os.makedirs(folder_3, exist_ok=True)

    i = 1
    for g in uniform_groups:
        df = pd.DataFrame(g, columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder_3, f"g_{i}.csv")
        df.to_csv(csv_path, index = True)
        i += 1
        
    ##batch_wise_mix_summary----
    summary_output = [[0 for j in range(tot_branches + 1)] for i in range(len(groups_branch_wise))]
    sorted_branch_arr = sorted(brach_arr)
    for ib, br in enumerate(sorted_branch_arr):
        for ig, g_i in enumerate(groups_branch_wise):
            count = 0
            for entries in g_i:
                if entries[0][4:6] == br:
                    count += 1
            summary_output[ig][ib] = count
    for i in range((len(groups_branch_wise))):
        sum = 0
        for j in range(tot_branches):
            sum += summary_output[i][j]
        summary_output[i][tot_branches] = sum

    rows = []    
    for i in range(len(groups_branch_wise)):
        file_name = f"G{i + 1}"
        rows.append(file_name)
        
    cols = []
    cols.extend(sorted_branch_arr)
    cols.append("Total")
    df = pd.DataFrame(
            summary_output,
            columns = cols,
            index = rows
    )

    ##uniform mix ----
    summary_output_2 = [[0 for j in range(tot_branches + 1)] for i in range(group_nums)]
    for ib, br in enumerate(sorted_branch_arr):
        for ig, g_i in enumerate(uniform_groups):
            count = 0
            for entries in g_i:
                if entries[0][4:6] == br:
                    count += 1
            summary_output_2[ig][ib] = count
    for i in range(group_nums):
        sum = 0
        for j in range(tot_branches):
            sum += summary_output_2[i][j]
        summary_output_2[i][tot_branches] = sum

    rows = []    
    for i in range(group_nums):
        file_name = f"G{i + 1}"
        rows.append(file_name)
        
    cols = []
    cols.extend(sorted_branch_arr)
    cols.append("Total")
    df_2 = pd.DataFrame(
            summary_output_2,
            columns = cols,
            index = rows
    )

    ##merging and creating summary csv file
    with open("summary.csv", "w") as f:
        df.to_csv(f, index=True)
        f.write("\n")  # blank line between tables
        df_2.to_csv(f, index=True)
        
    return[folder, folder_2, folder_3, 'summary.csv']
        
def main(choice, file):
        if choice == 1:
            row_adder(file)
        else:
            inp_data_set = pd.DataFrame(pd.read_csv(file))
            ret_list = output_generator(inp_data_set)
            st.session_state.append(ret_list)
            st.session_state['uploaded_file'] = None
            zip_buffer = io.BytesIO()
            zip_buffer = io.BytesIO()
            with zp.ZipFile(zip_buffer, "w", zp.ZIP_DEFLATED) as zipf:
                for file_path in ret_list:
                    if os.path.exists(file_path):  # make sure file exists
                        arcname = os.path.basename(file_path)  # store only filename inside ZIP
                        zipf.write(file_path, arcname=arcname)
            zip_buffer.seek(0)
                    
            if st.button("Create ZIP and Download"):
                st.download_button(
                    label="Download files",
                    data=zip_buffer,
                    file_name="selected_files.zip",
                    mime="application/zip"
                )
            st.experimental_rerun()
            
            
if __name__ == 'main':
    st.title('File processor')
    if 'results' not in st.session_state:
        st.session_state.results = []
    uploaded_file = st.file_uploader('upload your csv file', type = ['csv'])
    if uploaded_file is not None:
        choice = int(input())
        main(choice, uploaded_file)