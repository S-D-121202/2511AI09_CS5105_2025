import streamlit as st
import pandas as pd
import numpy as np
import logging
from io import BytesIO

# ---------------- LOGGER SETUP ----------------
logging.basicConfig(
    filename="app.log",             # Log file name
    level=logging.INFO,             # Logging level
    format="%(asctime)s - %(levelname)s - %(message)s"
)
logger = logging.getLogger()

# ---------------- CLASS DEFINITION ----------------
class file_operator:
    def __init__(self, df):
        try:
            self.data = df.copy()
            self.parameter_calc()
            self.main_func()
            self.output_file_creator()
            logger.info("File operator initialized successfully.")
        except Exception as e:
            logger.exception(f"Initialization failed: {e}")
            raise

    def parameter_calc(self):
        try:
            self.data.sort_values(by=self.data.columns[3], ascending=False, inplace=True)
            self.fac_size = self.data.shape[1] - 4
            self.group_size = self.fac_size
            self.tot_groups = (self.data.shape[0] // self.group_size) + 1
            logger.info(f"Parameters calculated: fac_size={self.fac_size}, tot_groups={self.tot_groups}")
        except Exception as e:
            logger.exception(f"Error during parameter calculation: {e}")
            raise

    def main_func(self):
        try:
            N = self.tot_groups
            faculy_alloc = {roll: '' for roll in self.data['Roll']}
            student_alloc = {j: [] for j in self.data.columns[4:]}
            student_alloc_count = {j: 0 for j in self.data.columns[4:]}
            self.faculty_pref_prior_count = {j: [] for j in self.data.columns[4:]}

            # Faculty preference count
            for j in self.data.columns[4:]:
                c = {i: 0 for i in range(1, self.fac_size + 1)}
                for i in range(1, self.fac_size + 1):
                    for k in self.data[j]:
                        if k == i:
                            c[i] += 1
                    self.faculty_pref_prior_count[j].append(c[i])

            df = pd.DataFrame(self.faculty_pref_prior_count).T
            df.reset_index(inplace=True)
            col = ['Faculty'] + [f'{j}_preference_count' for j in range(1, self.fac_size + 1)]
            df.columns = col
            self.fac_pref_df = df

            count = 0
            for i in range(N - 1):
                vis = {j: False for j in self.data.columns[4:]}
                for st_ in range(count, count + self.group_size):
                    priority = 1
                    row_slice = self.data.iloc[st_, 4:]
                    while vis[self.data.columns[4:][row_slice == priority][0]]:
                        priority += 1
                    fac = self.data.columns[4:][row_slice == priority][0]
                    vis[fac] = True
                    faculy_alloc[self.data.iloc[st_, 0]] = fac
                    student_alloc[fac].append(self.data.iloc[st_, 0])
                    student_alloc_count[fac] += 1
                count += self.group_size

            vis = {j: False for j in self.data.columns[4:]}
            for st_ in range(count, self.data.shape[0]):
                priority = 1
                row_slice = self.data.iloc[st_, 4:]
                while vis[self.data.columns[4:][row_slice == priority][0]]:
                    priority += 1
                fac = self.data.columns[4:][row_slice == priority][0]
                vis[fac] = True
                faculy_alloc[self.data.iloc[st_, 0]] = fac
                student_alloc[fac].append(self.data.iloc[st_, 0])
                student_alloc_count[fac] += 1

            self.faculy_alloc = faculy_alloc
            self.student_alloc = student_alloc
            self.student_alloc_count = student_alloc_count

            logger.info("Main allocation function completed successfully.")

        except Exception as e:
            logger.exception(f"Error during main function: {e}")
            raise

    def output_file_creator(self):
        try:
            self.output_btp_mtp_allocation = self.data.iloc[:, 0:4].copy()
            self.output_btp_mtp_allocation['Allocated'] = [fac for fac in self.faculy_alloc.values()]

            self.output_btp_mtp_allocation_cgpa_sorted = self.output_btp_mtp_allocation.sort_values(
                by=self.data.columns[3], ascending=False
            )
            self.output_btp_mtp_allocation_name_sorted = self.output_btp_mtp_allocation.sort_values(
                by='Name', ascending=True
            )
            logger.info("Output files generated successfully.")
        except Exception as e:
            logger.exception(f"Error while creating output files: {e}")
            raise


# ---------------- STREAMLIT APP ----------------
st.set_page_config(page_title="BTP/MTP Allocation", layout="centered")
st.title("BTP/MTP Allocation System")
st.write("Upload your student preference CSV file and download all outputs after running allocation once.")

uploaded_file = st.file_uploader("Upload input_btp_mtp_allocation.csv", type=["csv"])

if uploaded_file is not None:
    try:
        df = pd.read_csv(uploaded_file)
        st.success("File uploaded successfully.")
        st.dataframe(df.head())

        if st.button("Run Allocation"):
            try:
                FO = file_operator(df)
                st.session_state['allocation_done'] = True
                st.session_state['FO'] = FO
                st.success("Allocation completed successfully.")
                logger.info("Allocation run successfully via Streamlit.")
            except Exception as e:
                st.error(f"Error during allocation: {e}")
                logger.exception(f"Error during Streamlit allocation: {e}")

    except Exception as e:
        st.error(f"Error reading file: {e}")
        logger.exception(f"Error reading uploaded CSV: {e}")

if 'allocation_done' in st.session_state and st.session_state['allocation_done']:
    FO = st.session_state['FO']

    try:
        pref_buffer = BytesIO()
        out1_buffer = BytesIO()
        out2_buffer = BytesIO()

        FO.fac_pref_df.to_csv(pref_buffer, index=False)
        FO.output_btp_mtp_allocation_cgpa_sorted.to_csv(out1_buffer, index=False)
        FO.output_btp_mtp_allocation_name_sorted.to_csv(out2_buffer, index=False)

        pref_buffer.seek(0)
        out1_buffer.seek(0)
        out2_buffer.seek(0)

        st.download_button(
            label="Download Faculty Preference Count",
            data=pref_buffer,
            file_name="fac_preference_count.csv",
            mime="text/csv"
        )

        st.download_button(
            label="Download CGPA Sorted Allocation",
            data=out1_buffer,
            file_name="output_btp_mtp_allocation_cgpa_sorted.csv",
            mime="text/csv"
        )

        st.download_button(
            label="Download Name Sorted Allocation",
            data=out2_buffer,
            file_name="output_btp_mtp_allocation.csv",
            mime="text/csv"
        )

        st.subheader("Faculty Preference Summary")
        st.dataframe(FO.fac_pref_df)

        st.subheader("Sample Allocation Output")
        st.dataframe(FO.output_btp_mtp_allocation_name_sorted.head())

    except Exception as e:
        st.error(f"Error preparing download files: {e}")
        logger.exception(f"Error preparing download files: {e}")
