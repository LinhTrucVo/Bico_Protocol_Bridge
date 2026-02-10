# PowerShell script to rename functions in Unit.c files
# This script adds "Unit" suffix to all function implementations

param(
    [Parameter(Mandatory=$true)]
    [string]$ComponentName,
    
    [Parameter(Mandatory=$true)]
    [string]$UnitCFile
)

# Read the file content
$content = Get-Content -Path $UnitCFile -Raw

# Define the function naming patterns
$patterns = @{
    "${ComponentName}_Init" = "${ComponentName}Unit_Init"
    "${ComponentName}_Configure" = "${ComponentName}Unit_Configure"
    "${ComponentName}_Send" = "${ComponentName}Unit_Send"
    "${ComponentName}_Receive" = "${ComponentName}Unit_Receive"
    "${ComponentName}_Write" = "${ComponentName}Unit_Write"
    "${ComponentName}_Read" = "${ComponentName}Unit_Read"
    "${ComponentName}_Start" = "${ComponentName}Unit_Start"
    "${ComponentName}_Stop" = "${ComponentName}Unit_Stop"
    "${ComponentName}_Set" = "${ComponentName}Unit_Set"
    "${ComponentName}_Get" = "${ComponentName}Unit_Get"
    "${ComponentName}_Enable" = "${ComponentName}Unit_Enable"
    "${ComponentName}_Disable" = "${ComponentName}Unit_Disable"
    "${ComponentName}_Register" = "${ComponentName}Unit_Register"
    "${ComponentName}_DeInit" = "${ComponentName}Unit_DeInit"
    "${ComponentName}_Erase" = "${ComponentName}Unit_Erase"
    "${ComponentName}_Flush" = "${ComponentName}Unit_Flush"
    "${ComponentName}_Toggle" = "${ComponentName}Unit_Toggle"
    "${ComponentName}_Scan" = "${ComponentName}Unit_Scan"
    "${ComponentName}_Is" = "${ComponentName}Unit_Is"
    "${ComponentName}_Calculate" = "${ComponentName}Unit_Calculate"
    "${ComponentName}_Verify" = "${ComponentName}Unit_Verify"
    "${ComponentName}_Select" = "${ComponentName}Unit_Select"
    "${ComponentName}_Deselect" = "${ComponentName}Unit_Deselect"
    "${ComponentName}_Transmit" = "${ComponentName}Unit_Transmit"
}

# Replace function definitions and calls
foreach ($old in $patterns.Keys) {
    $new = $patterns[$old]
    $content = $content -replace "(?m)^(\s*)$old\(", "`$1$new("
    $content = $content -replace "([^a-zA-Z0-9_])$old\(", "`$1$new("
}

# Update the header comment
$content = $content -replace "// .* Driver Unit Implementation", "// This file is used to define the public interface of the component unit.`n// It contains public macros, private variables, and function definitions."

# Add Local Macros section if not present
if ($content -notmatch "//============================================================================\s+// Local Macros") {
    $content = $content -replace "(//============================================================================\s+// Local Types)", "//============================================================================`n// Local Macros`n//============================================================================`n`n`$1"
}

# Save the updated content
Set-Content -Path $UnitCFile -Value $content -NoNewline

Write-Host "Updated $UnitCFile successfully"
