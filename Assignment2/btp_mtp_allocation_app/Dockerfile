# ---- Base Image ----
FROM python:3.11-slim

# ---- Metadata ----
LABEL maintainer="Swaren Rex <swaren.rex@example.com>"
LABEL description="Dockerized Streamlit App for BTP/MTP Allocation"

# ---- Set working directory ----
WORKDIR /app

# ---- Copy project files ----
COPY requirements.txt .
COPY btp_mtp_allocation_app.py .

# ---- Install dependencies ----
RUN pip install --no-cache-dir -r requirements.txt

# ---- Expose Streamlit default port ----
EXPOSE 8501

# ---- Set environment variables ----
ENV PYTHONUNBUFFERED=1 \
    STREAMLIT_SERVER_ENABLECORS=false \
    STREAMLIT_SERVER_HEADLESS=true \
    STREAMLIT_SERVER_PORT=8501

# ---- Command to run Streamlit ----
CMD ["streamlit", "run", "btp_mtp_allocation_app.py"]
