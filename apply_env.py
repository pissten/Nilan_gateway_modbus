import os

try:
    from dotenv import load_dotenv
    load_dotenv()
except ImportError:
    # If python-dotenv is not installed, we can try to manually parse or just rely on system env.
    # For PIO, often it's better to just read the file manually if we don't want dependencies.
    if os.path.exists(".env"):
        with open(".env") as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                if "=" in line:
                    k, v = line.split("=", 1)
                    os.environ[k.strip()] = v.strip().strip('"').strip("'")

Import("env")

# List of secrets to inject
secrets = [
    "WIFI_SSID",
    "WIFI_PASSWORD",
    "MQTT_SERVER",
    "MQTT_USERNAME",
    "MQTT_PASSWORD"
]

defines = []
for secret in secrets:
    value = os.environ.get(secret)
    if value:
        # Stringify the value for C++
        defines.append((secret, f'"{value}"'))

env.Append(CPPDEFINES=defines)
