# Run Waf to configure and build
./waf configure build --debug

# Add the bin directory to PATH temporarily for the current session
$bin = ".\bin"  # Adjust this if your bin path is different

$env:Path += ";$bin"

# Inform the user
Write-Host "Added to PATH temporarily for the current session." -ForegroundColor Green

# Start the main executable
Start-Process "./build_output/main.exe"
