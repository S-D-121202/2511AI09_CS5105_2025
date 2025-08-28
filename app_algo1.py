import streamlit as st
import pandas as pd
import copy as co
import csv as cs
import os
import re
import io
import zipfile as zp

# ---------------------------
# Row addition (Streamlit form)
# ---------------------------
def row_adder(csv_file, row):
    with open(csv_file, mode='a', newline='') as file:
        writer = cs.writer(file)
        writer.writerow(row)    

def row_addition_section(uploaded_file):
    st.subheader("Add a Row to CSV")
    roll = st.text_input("Roll (format: 4 digits + 2 letters + 2 digits, e.g. 2021CS01)")
    name = st.text_input("Name (First Last, e.g. John Doe)")
    email = st.text_input("Email (e.g. abc@xyz.co.in)")

    if st.button("Add Row"):
        roll_pattern = r'^\d{4}[A-Z]{2}\d{2}$'
        name_pattern = r'^[A-Z][a-z]+ [A-Z][a-z]+$'
        email_pattern = r'^[a-z]+@[a-z]+\.co\.in$'

        if not re.match(roll_pattern, roll):
            st.error("Invalid roll format")
            return
        if not re.match(name_pattern, name):
            st.error("Invalid name format")
            return
        if not re.match(email_pattern, email):
            st.error("Invalid email format")
            return

        row_adder(uploaded_file.name, [roll, name, email])
        st.success("Row added successfully!")

# ---------------------------
# Output generator (same logic as before)
# ---------------------------
def output_generator(inp_data_set, group_nums):
    braches = {}
    branch_count = {}

    for st_ in inp_data_set.itertuples(index=True):
        if st_.Roll[4:6] not in braches.keys():
            braches.update({st_.Roll[4:6]: [[st_.Roll, st_.Name, st_.Email]]})
            branch_count.update({st_.Roll[4:6]: 1})
        else:
            braches[st_.Roll[4:6]].append([st_.Roll, st_.Name, st_.Email])
            branch_count[st_.Roll[4:6]] += 1

    # Folders for outputs
    folder = 'output_batch_list'
    os.makedirs(folder, exist_ok=True)

    for st_ in braches.keys():
        df = pd.DataFrame(braches[st_], columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder, f"{st_}.csv")
        df.to_csv(csv_path, index=True)
        
    # Groups
    max_person_per_group = len(inp_data_set) // group_nums + 1

    brach_arr = list(braches.keys())
    tot_branches = len(brach_arr)

    ## Branch-wise mix
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

    for i, g in enumerate(groups_branch_wise, start=1):
        df = pd.DataFrame(g, columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder_2, f"g_{i}.csv")
        df.to_csv(csv_path, index=True)
        
    ## Uniform mix
    sorted_branch_count = dict(sorted(branch_count.items(), key=lambda item: item[1], reverse=True))
    sorted_branch_arr = list(sorted_branch_count.keys())
    branch_count_copy_2 = co.deepcopy(branch_count)
    g_i = 0

    max_br = sorted_branch_arr[0]
    uniform_groups = []
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
                max_br = max(branch_count_copy_2, key=branch_count_copy_2.get)
        max_br = max(branch_count_copy_2, key=branch_count_copy_2.get)
        uniform_groups.append(group_i)
        g_i += 1
        
    folder_3 = 'output_uniform_mix'
    os.makedirs(folder_3, exist_ok=True)

    for i, g in enumerate(uniform_groups, start=1):
        df = pd.DataFrame(g, columns=["Roll", "Name", "Email"])
        csv_path = os.path.join(folder_3, f"g_{i}.csv")
        df.to_csv(csv_path, index=True)
        
    ## Summaries
    summary_output = [[0 for j in range(tot_branches + 1)] for i in range(len(groups_branch_wise))]
    sorted_branch_arr = sorted(brach_arr)
    for ib, br in enumerate(sorted_branch_arr):
        for ig, g_i in enumerate(groups_branch_wise):
            count = sum(1 for entries in g_i if entries[0][4:6] == br)
            summary_output[ig][ib] = count
    for i in range(len(groups_branch_wise)):
        summary_output[i][tot_branches] = sum(summary_output[i][:tot_branches])

    rows = [f"G{i+1}" for i in range(len(groups_branch_wise))]
    cols = sorted_branch_arr + ["Total"]
    df = pd.DataFrame(summary_output, columns=cols, index=rows)

    summary_output_2 = [[0 for j in range(tot_branches + 1)] for i in range(group_nums)]
    for ib, br in enumerate(sorted_branch_arr):
        for ig, g_i in enumerate(uniform_groups):
            count = sum(1 for entries in g_i if entries[0][4:6] == br)
            summary_output_2[ig][ib] = count
    for i in range(group_nums):
        summary_output_2[i][tot_branches] = sum(summary_output_2[i][:tot_branches])

    rows = [f"G{i+1}" for i in range(group_nums)]
    df_2 = pd.DataFrame(summary_output_2, columns=cols, index=rows)

    with open("summary.csv", "w") as f:
        df.to_csv(f, index=True)
        f.write("\n")
        df_2.to_csv(f, index=True)
        
    return [folder, folder_2, folder_3, 'summary.csv']

# ---------------------------
# Main Streamlit app
# ---------------------------
def main():
    st.title('File Processor')

    uploaded_file = st.file_uploader('Upload your CSV file', type=['csv'])
    
    if uploaded_file is not None:
        df = pd.read_csv(uploaded_file)
        st.write("Preview of uploaded data:")
        st.dataframe(df.head())

        choice = st.radio("Choose an option:", ["Add Row", "Process CSV"])

        if choice == "Add Row":
            row_addition_section(uploaded_file)

        elif choice == "Process CSV":
            group_nums = st.number_input("Enter number of groups", min_value=1, step=1)
            if st.button("Process File"):
                ret_list = output_generator(df, group_nums)

                # Create ZIP
                zip_buffer = io.BytesIO()
                with zp.ZipFile(zip_buffer, "w", zp.ZIP_DEFLATED) as zipf:
                    for file_path in ret_list:
                        if os.path.exists(file_path):
                            if os.path.isdir(file_path):
                                for root, _, files in os.walk(file_path):
                                    for f in files:
                                        full_path = os.path.join(root, f)
                                        arcname = os.path.relpath(full_path, start=os.path.dirname(file_path))
                                        zipf.write(full_path, arcname=arcname)
                            else:
                                arcname = os.path.basename(file_path)
                                zipf.write(file_path, arcname=arcname)
                zip_buffer.seek(0)

                st.download_button(
                    label="Download All Results (ZIP)",
                    data=zip_buffer,
                    file_name="results.zip",
                    mime="application/zip"
                )

if __name__ == "__main__":
    main()

